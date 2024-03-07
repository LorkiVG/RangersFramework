#include "Resolution.h"
#include "File.h"
#include "Path.h"

namespace Resolution {
    int GetScreenWidth() 
    {
        return GetSystemMetrics(SM_CXSCREEN);
    }
    int GetScreenHeight() 
    {
        return GetSystemMetrics(SM_CYSCREEN);
    }
    int GetProgramWidth() 
    {
        int res = Strings::ConvertToInt(Strings::GetParSepStr(File::GetParFromFile(L"\\SpaceRangersHD\\CFG.txt", L"VideoMode"), L",", 0));
        if (res) 
        {
            return res;
        }
        else 
        {
            return GetScreenWidth();
        }
    }
    int GetProgramHeight() 
    {
        int res = Strings::ConvertToInt(Strings::GetParSepStr(File::GetParFromFile(L"\\SpaceRangersHD\\CFG.txt", L"VideoMode"), L",", 1));
        if (res) 
        {
            return res;
        }
        else 
        {
            return GetScreenHeight();
        }
    }
};