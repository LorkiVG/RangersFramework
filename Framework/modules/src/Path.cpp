#include "Path.h"
#include <iostream>
#include <string>
#include <fstream>

namespace Path 
{
    wstring utilitiesdir = L"";
    char* utilitiesdir_char = "";

    wstring documents_folder = L"";
    char* documents_folder_char = "";

    wstring log_path = L"";
    char* log_path_char = "";

    void InitUtilitiesPath(HMODULE hModule)
    {
        WCHAR utilities_dir_path[MAX_PATH];
        GetModuleFileNameW(hModule, utilities_dir_path, MAX_PATH);
        utilitiesdir = utilities_dir_path;

        GetModuleFileNameA(hModule, utilitiesdir_char, MAX_PATH);
    }
    void InitUserDocumentsPath() 
    {
        WCHAR user_documents_path[MAX_PATH];
        SHGetSpecialFolderPathW(0, user_documents_path, CSIDL_PERSONAL, true);
        documents_folder = user_documents_path;
         
        SHGetSpecialFolderPathA(0, documents_folder_char, CSIDL_PERSONAL, true);
    }
    void InitLogPath() 
    {
        log_path = documents_folder + L"/SpaceRangersHD/########.log";
        log_path_char = strcat(documents_folder_char, "/SpaceRangersHD/########.log");
    }
}