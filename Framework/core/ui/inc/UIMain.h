#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <shlobj.h>

using namespace std;

namespace UI
{
    extern HWND hParentWindow;
    void Init();
    void Shutdown();
    void Render();
}