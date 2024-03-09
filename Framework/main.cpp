#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
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
            

            // bool success = Rml::LoadFontFace("assets/my_font_face.ttf");

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

            Logger::WriteChar("Find main window");
            hParentWindow = FindWindowA("Rangers MainClassName", "Rangers");
            
            Logger::WriteChar("Init UI Process");
            
            if (!Backend::Initialize(hParentWindow))
            {
                Backend::Shutdown();
                return -1;
            }

            // Install the custom interfaces constructed by the backend before initializing RmlUi.
            Rml::SetSystemInterface(Backend::GetSystemInterface());
            Rml::SetRenderInterface(Backend::GetRenderInterface());

            // RmlUi initialisation.
            Rml::Initialise();

            Logger::WriteChar("Init RmlUIContext");
            Rml::Context* context = Rml::CreateContext("default", Rml::Vector2i(1028, 720));

            RECT rect;
            if(GetWindowRect(hParentWindow, &rect))
            {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
            }

            return 0;

            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
