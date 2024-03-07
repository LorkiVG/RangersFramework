#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "windows.h"
using namespace std;

namespace File 
{
    void Rename(wchar_t* oldfilename,wchar_t* newfilename);
    inline bool FileExists(const wstring& name);
    void FileEncryptLcf(wchar_t* filepath, uint32_t key, byte key2, byte key3,wchar_t* newfilename);
    void FileDecryptLcf(wchar_t* filepath, uint32_t key, byte key2, byte key3, wchar_t* newfilename);
    wchar_t* GetParFromFile(wchar_t* txt_path, wchar_t* param_name);
    wchar_t* SetParFromFile(wchar_t* txt_path, wchar_t* param_name, wchar_t* value);
};