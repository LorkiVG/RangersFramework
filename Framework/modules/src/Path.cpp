#include "Path.h"
#include <iostream>
#include <string>
#include <fstream>

namespace Path 
{
    wstring utilitiesPath = L"";
    char* utilitiesPath_char = "";

    wstring modsPath = L"";
    char* modsPath_char = "";

    wstring documentsPath = L"";
    char* documentsPath_char = "";

    wstring logPath = L"";
    char* logPath_char = "";

    void InitUtilitiesPath(HMODULE hModule)
    {
        WCHAR utilitiesPath_temp[MAX_PATH];
        GetModuleFileNameW(hModule, utilitiesPath_temp, MAX_PATH);
        utilitiesPath = utilitiesPath_temp;

        GetModuleFileNameA(hModule, utilitiesPath_char, MAX_PATH);
    }

    void InitModsPath()
    {
        modsPath = utilitiesPath + L"/Mods";
        modsPath_char = strcat(utilitiesPath_char, "/Mods");
    }

    void InitDocumentsPath() 
    {
        WCHAR documentsPath_temp[MAX_PATH];
        SHGetSpecialFolderPathW(0, documentsPath_temp, CSIDL_PERSONAL, true);
        documentsPath = documentsPath_temp;
         
        SHGetSpecialFolderPathA(0, documentsPath_char, CSIDL_PERSONAL, true);
    }

    void InitLogPath() 
    {
        logPath = documentsPath + L"/SpaceRangersHD/########.log";
        logPath_char = strcat(documentsPath_char, "/SpaceRangersHD/########.log");
    }
}