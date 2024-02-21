#include <fstream>
#include <windows.h>
#include <TlHelp32.h>

#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma comment(lib,"ntdll.lib")

typedef HMODULE(WINAPI* pLoadLibraryA)(LPCSTR);
typedef FARPROC(WINAPI* pGetProcAddress)(HMODULE, LPCSTR);

typedef BOOL(WINAPI* PDLL_MAIN)(HMODULE, DWORD, PVOID);

typedef struct _MANUAL_INJECT
{
	PVOID ImageBase;
	PIMAGE_NT_HEADERS NtHeaders;
	PIMAGE_BASE_RELOCATION BaseRelocation;
	PIMAGE_IMPORT_DESCRIPTOR ImportDirectory;
	pLoadLibraryA fnLoadLibraryA;
	pGetProcAddress fnGetProcAddress;
}MANUAL_INJECT, *PMANUAL_INJECT;


DWORD WINAPI LoadDll(PVOID p)
{
	PMANUAL_INJECT ManualInject;

	HMODULE hModule;
	DWORD i, Function, count, delta;

	PDWORD ptr;
	PWORD list;

	PIMAGE_BASE_RELOCATION pIBR;
	PIMAGE_IMPORT_DESCRIPTOR pIID;
	PIMAGE_IMPORT_BY_NAME pIBN;
	PIMAGE_THUNK_DATA FirstThunk, OrigFirstThunk;

	PDLL_MAIN EntryPoint;

	ManualInject = (PMANUAL_INJECT)p;

	pIBR = ManualInject->BaseRelocation;
	// Calculate delta
	delta = (DWORD)((LPBYTE)ManualInject->ImageBase - ManualInject->NtHeaders->OptionalHeader.ImageBase); 

	// Relocate image
	while (pIBR->VirtualAddress)
	{
		if (pIBR->SizeOfBlock >= sizeof(IMAGE_BASE_RELOCATION))
		{
			count = (pIBR->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
			list = (PWORD)(pIBR + 1);

			for (i = 0; i < count; i++)
			{
				if (list[i])
				{
					ptr = (PDWORD)((LPBYTE)ManualInject->ImageBase + (pIBR->VirtualAddress + (list[i] & 0xFFF)));
					*ptr += delta;
				}
			}
		}

		pIBR = (PIMAGE_BASE_RELOCATION)((LPBYTE)pIBR + pIBR->SizeOfBlock);
	}

	pIID = ManualInject->ImportDirectory;

	// Resolve DLL imports
	while (pIID->Characteristics)
	{
		OrigFirstThunk = (PIMAGE_THUNK_DATA)((LPBYTE)ManualInject->ImageBase + pIID->OriginalFirstThunk);
		FirstThunk = (PIMAGE_THUNK_DATA)((LPBYTE)ManualInject->ImageBase + pIID->FirstThunk);

		hModule = ManualInject->fnLoadLibraryA((LPCSTR)ManualInject->ImageBase + pIID->Name);

		if (!hModule)
		{
			return FALSE;
		}

		while (OrigFirstThunk->u1.AddressOfData)
		{
			if (OrigFirstThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)
			{
				// Import by ordinal
				Function = (DWORD)ManualInject->fnGetProcAddress(hModule, (LPCSTR)(OrigFirstThunk->u1.Ordinal & 0xFFFF));

				if (!Function)
				{
					return FALSE;
				}

				FirstThunk->u1.Function = Function;
			}

			else
			{
				// Import by name
				pIBN = (PIMAGE_IMPORT_BY_NAME)((LPBYTE)ManualInject->ImageBase + OrigFirstThunk->u1.AddressOfData);
				Function = (DWORD)ManualInject->fnGetProcAddress(hModule, (LPCSTR)pIBN->Name);

				if (!Function)
				{
					return FALSE;
				}

				FirstThunk->u1.Function = Function;
			}

			OrigFirstThunk++;
			FirstThunk++;
		}

		pIID++;
	}

	if (ManualInject->NtHeaders->OptionalHeader.AddressOfEntryPoint)
	{
		EntryPoint = (PDLL_MAIN)((LPBYTE)ManualInject->ImageBase + ManualInject->NtHeaders->OptionalHeader.AddressOfEntryPoint);
		return EntryPoint((HMODULE)ManualInject->ImageBase, DLL_PROCESS_ATTACH, NULL); // Call the entry point
	}

	return TRUE;
}

DWORD WINAPI LoadDllEnd()
{
	return 0;
}

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

char shellCode[] =
{
	0x60, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x81, 0xEB, 0x06, 0x00, 0x00, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0xBA, 0xCC, 0xCC, 0xCC, 0xCC, 0x52, 0xFF, 0xD0, 0x61, 0x68, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3
};


int main()
{
	LPBYTE ptr;
	HANDLE hProcess, hThread, hFile;
	PVOID mem, mem1;
	DWORD ProcessId, FileSize, read, i;
	PVOID buffer, image;
	BOOLEAN bl;
	PIMAGE_DOS_HEADER pIDH;
	PIMAGE_NT_HEADERS pINH;
	PIMAGE_SECTION_HEADER pISH;

	CONTEXT ctx;

	MANUAL_INJECT ManualInject;

	std::ofstream logFile("RangersVG.log", std::ios::trunc);

	logFile << "RangersVG STARTED" << std::endl;

	const char* exePath = "Rangers.exe";
	const char* dllPath = "VGFramework.dll";

	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// Opening Rangers.exe
	logFile << "Opening Rangers.exe" << std::endl;
	if (!CreateProcessA(exePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
	{
		logFile << "Error: Unable to open the Rangers.exe" << GetLastError() << std::endl;
		return -1;
	}


	ctx.ContextFlags = CONTEXT_FULL;

	// Opening VGFramework.dll
	logFile << "Opening VGFramework.dll" << std::endl;
	hFile = CreateFile(dllPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL); // Open the DLL

	if (hFile == INVALID_HANDLE_VALUE)
	{
		logFile << "Error: Unable to open VGFramework.dll " << GetLastError() << std::endl;
		return -1;
	}

	// Allocate buffer for DLL
	FileSize = GetFileSize(hFile, NULL);
	buffer = VirtualAlloc(NULL, FileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!buffer)
	{
		logFile << "Error: Unable to allocate memory for VGFramework.dll data " << GetLastError() << std::endl;

		CloseHandle(hFile);
		return -1;
	}

	// Read DLL to buffer
	if (!ReadFile(hFile, buffer, FileSize, &read, NULL))
	{
		logFile << "Error: Unable to read the VGFramework.dll " << GetLastError() << std::endl;

		VirtualFree(buffer, 0, MEM_RELEASE);
		CloseHandle(hFile);

		return -1;
	}
	CloseHandle(hFile);

	pIDH = (PIMAGE_DOS_HEADER)buffer;

	if (pIDH->e_magic != IMAGE_DOS_SIGNATURE)
	{
		logFile << "Error: Invalid executable image" << std::endl;

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}
	pINH = (PIMAGE_NT_HEADERS)((LPBYTE)buffer + pIDH->e_lfanew);

	if (pINH->Signature != IMAGE_NT_SIGNATURE)
	{
		logFile << "Error: Invalid PE header" << std::endl;

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}
	if (!(pINH->FileHeader.Characteristics & IMAGE_FILE_DLL))
	{
		logFile << "Error: The image is not VGFramework.dll" << std::endl;

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}


	//Set debug privilege
	RtlAdjustPrivilege(20, TRUE, FALSE, &bl);

	//Opening target process handle
	logFile << "Opening target process handle" << std::endl;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
	if (!hProcess)
	{
		logFile << "Error: Unable to open target process handle" << GetLastError() << std::endl;
		return -1;
	}
	//Allocating memory for DLL
	logFile << "Allocating memory for VGFramework.dll" << std::endl;
	image = VirtualAllocEx(hProcess, NULL, pINH->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); // Allocate memory for the DLL
	if (!image)
	{
		logFile << "Error: Unable to allocate memory for VGFramework.dll " << GetLastError() << std::endl;

		VirtualFree(buffer, 0, MEM_RELEASE);
		CloseHandle(hProcess);

		return -1;
	}

	// Copy the header to target process
	logFile << "Copying headers into target process" << std::endl;
	if (!WriteProcessMemory(hProcess, image, buffer, pINH->OptionalHeader.SizeOfHeaders, NULL))
	{
		logFile << "Error: Unable to copy headers to target process " << GetLastError() << std::endl;

		VirtualFreeEx(hProcess, image, 0, MEM_RELEASE);
		CloseHandle(hProcess);

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}
	pISH = (PIMAGE_SECTION_HEADER)(pINH + 1);

	// Copy DLL to target process
	logFile << "Copying sections to target process" << std::endl;
	for (i = 0; i < pINH->FileHeader.NumberOfSections; i++)
	{
		WriteProcessMemory(hProcess, (PVOID)((LPBYTE)image + pISH[i].VirtualAddress), (PVOID)((LPBYTE)buffer + pISH[i].PointerToRawData), pISH[i].SizeOfRawData, NULL);
	}

	//Allocating memory for the loader code
	logFile << "Allocating memory for loader code" << std::endl;
	mem1 = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!mem1)
	{
		logFile << "Error: Unable to allocate memory for loader code " << GetLastError() << std::endl;

		VirtualFreeEx(hProcess, image, 0, MEM_RELEASE);
		CloseHandle(hProcess);

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}

	logFile << "Loader code allocated at " << mem1 << std::endl;
	memset(&ManualInject, 0, sizeof(MANUAL_INJECT));
	ManualInject.ImageBase = image;
	ManualInject.NtHeaders = (PIMAGE_NT_HEADERS)((LPBYTE)image + pIDH->e_lfanew);
	ManualInject.BaseRelocation = (PIMAGE_BASE_RELOCATION)((LPBYTE)image + pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	ManualInject.ImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((LPBYTE)image + pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	ManualInject.fnLoadLibraryA = LoadLibraryA;
	ManualInject.fnGetProcAddress = GetProcAddress;


	logFile << "Writing loader code to target process" << std::endl;
	WriteProcessMemory(hProcess, mem1, &ManualInject, sizeof(MANUAL_INJECT), NULL); // Write the loader information to target process
	WriteProcessMemory(hProcess, (PVOID)((PMANUAL_INJECT)mem1 + 1), LoadDll, (DWORD)LoadDllEnd - (DWORD)LoadDll, NULL); // Write the loader code to target process


	logFile << "Allocating memory in target process" << std::endl;
	mem = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!mem)
	{
		logFile << "Error: Unable to allocate memory in target process " << GetLastError() << std::endl;

		CloseHandle(hProcess);
		return -1;
	}
	logFile << "Memory allocated at " << mem << std::endl;



	//Opening target thread handle
	logFile << "Opening target thread handle" << std::endl;
	hThread = pi.hThread;
	if (!hThread)
	{
		logFile << "Error: Unable to open target thread handle " << GetLastError() << std::endl;

		VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return -1;
	}


	//Suspending after SFT_Init
	Sleep(1000);
	logFile << "Suspending target thread" << std::endl;
	SuspendThread(hThread);
	GetThreadContext(hThread, &ctx);


	// Allocating buffer for shellCode
	buffer = VirtualAlloc(NULL, 65536, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	ptr = (LPBYTE)buffer;
	memcpy(buffer, shellCode, sizeof(shellCode));
	while (1)
	{
		if (*ptr == 0xB8 && *(PDWORD)(ptr + 1) == 0xCCCCCCCC)
		{
			*(PDWORD)(ptr + 1) = (DWORD)((PMANUAL_INJECT)mem1 + 1);
		}

		if (*ptr == 0x68 && *(PDWORD)(ptr + 1) == 0xCCCCCCCC)
		{
			*(PDWORD)(ptr + 1) = ctx.Eip;
		}

		if (*ptr == 0xba && *(PDWORD)(ptr + 1) == 0xCCCCCCCC)
		{
			*(PDWORD)(ptr + 1) = (DWORD)(mem1);
		}

		if (*ptr == 0xC3)
		{
			ptr++;
			break;
		}

		ptr++;
	}

	// Writing shellCode from buffer into target process
	logFile << "Writing shellcode into target process" << std::endl;
	if (!WriteProcessMemory(hProcess, mem, buffer, sizeof(shellCode), NULL))
	{
		logFile << "Error: Unable to write shellcode into target process " << GetLastError() << std::endl;

		VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
		ResumeThread(hThread);

		CloseHandle(hThread);
		CloseHandle(hProcess);

		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}

	// Hijacking target thread
	ctx.Eip = (DWORD)mem;
	logFile << "Hijacking target thread" << std::endl;
	if (!SetThreadContext(hThread, &ctx))
	{
		logFile << "Error: Unable to hijack target thread " << GetLastError() << std::endl;

		VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
		ResumeThread(hThread);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		VirtualFree(buffer, 0, MEM_RELEASE);
		return -1;
	}


	logFile << "Resuming target thread" << std::endl;
	
	ResumeThread(hThread);

	logFile.close();
	CloseHandle(hThread);
	CloseHandle(hProcess);
	VirtualFree(buffer, 0, MEM_RELEASE);
	return 0;
}