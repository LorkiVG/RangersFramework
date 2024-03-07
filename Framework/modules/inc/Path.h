#pragma once
#include <string>
#include <windows.h>
#include <shlobj.h>

using namespace std;

namespace Path 
{
    extern wstring utilitiesdir;
    extern char* utilitiesdir_char;

    extern wstring documents_folder;
    extern char* documents_folder_char;

    extern wstring log_path;
    extern char* log_path_char;
    
    void InitUtilitiesPath(HMODULE hModule);
    void InitUserDocumentsPath ();
    void InitLogPath ();
}