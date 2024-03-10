#pragma once
#include <string>
#include <windows.h>
#include <shlobj.h>

using namespace std;

namespace Path 
{
    extern wstring utilitiesPath;
    extern char* utilitiesPath_char;

    extern wstring modsPath;
    extern char* modsPath_char;

    extern wstring documentsPath;
    extern char* documentsPath_char;

    extern wstring logPath;
    extern char* logPath_char;

    void InitUtilitiesPath(HMODULE hModule);
    void InitModsPath();
    void InitDocumentsPath();
    void InitLogPath();
}