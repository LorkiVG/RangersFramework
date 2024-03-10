#include "UIMain.h"
#include "MainLoop.h"
#include "Logger.h"
#include "MathHelper.h"

void MyEntryPointMainLoop()
{
    Logger::WriteMessage(L"Core UI Render 0");
    UI::Render();
}