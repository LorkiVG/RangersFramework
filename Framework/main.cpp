#pragma once
#include "TGalaxy.h"
#include "Path.h"
#include "Logger.h"
#include <string>
#include <vector>
using namespace std;

typedef void (__fastcall *TGalaxyNextDayType)(TGalaxy* galaxy);
TGalaxyNextDayType TGalaxyNextDay = nullptr;


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    HWND hParentWindow;
    uintptr_t targetAddr;
    void* hookAddr;
    ptrdiff_t offset;
    FILE* file;

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            setlocale(LC_ALL, "russian"); 
            srand(time(0)); 

            Path::InitUtilitiesPath(hModule);
            Path::InitUserDocumentsPath();
            Path::InitLogPath(); 

            Logger::WriteChar("VGFramework has been successfully added to the game");

            targetAddr = 0x00787E50;

            DWORD oldProtect;
            //Change memory protect to readwrite
            VirtualProtect((LPVOID)targetAddr, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

            file = fopen(Path::log_path_char, "a"); 
            fprintf(file, "%s\n", to_string((uint32_t)MyTGalaxyNextDayAsm).c_str()); 
            fclose(file); 

            // Get address hook function + (0x1 for skip priveled asm instruction on start)
            hookAddr = (void*)MyTGalaxyNextDayAsm;

            // Calculate relative offset for jmp
            offset = (ptrdiff_t)hookAddr - ((ptrdiff_t)targetAddr);
            offset = offset - sizeof(offset) - 0x1;

            // Write jmp opcode to memory
            *(unsigned char*)targetAddr = 0xE9;

            // Write relative offset to memory in little-endian format
            for (size_t i = 0; i < sizeof(offset); ++i) 
            {
                *((unsigned char*)(targetAddr)+i + 1) = (offset >> (8 * i)) & 0xFF;
            }

            //Change memory protect to readonly
            VirtualProtect((LPVOID)targetAddr, 5, oldProtect, &oldProtect);

            return 0;
            hParentWindow = FindWindowA("Rangers MainClassName", "Rangers");
            
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
