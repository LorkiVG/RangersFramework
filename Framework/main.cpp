#include "CoreMain.h"
#include "UIMain.h"
#include "Path.h"
#include "Logger.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>


using namespace std;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            setlocale(LC_ALL, "russian"); 
            srand(time(0)); 

            Path::InitUtilitiesPath(hModule);
            Path::InitModsPath();
            Path::InitDocumentsPath();
            Path::InitLogPath(); 

            Logger::WriteMessage(L"has been successfully added to game");
            
            Core::Init();
            UI::Init();

            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            UI::Shutdown();
            Core::Shutdown();
            Logger::WriteMessage(L"has been successfully disconnect from game");
            
            break;
    }
    return TRUE;
}
