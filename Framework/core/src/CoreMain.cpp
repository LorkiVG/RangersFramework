#include "Logger.h"
#include "OpcodeHelper.h"
#include "pointers.h"
#include "MainLoop.h"
#include "TGalaxy.h"
#include "CoreMain.h"

namespace Core
{
    void Init()
    {
        Logger::WriteMessage(L"Core Init");
        Logger::WriteMessage(L"Core Injection pathces to functions...");
        OpcodeHelper::InjectJmpToAddress(TGalaxyNextDay, (void*)MyTGalaxyNextDayAsm);
        Logger::WriteMessage(L"TGalaxyNextDay successfully patched");
        OpcodeHelper::InjectCallToAddress(CallMainLoopInEntryPoint, (void*)MyEntryPointMainLoopAsm);
        Logger::WriteMessage(L"EntryPointMainLoopCall successfully patched");
    }
    void Shutdown()
    {
        Logger::WriteMessage(L"Core Shutdown");
        OpcodeHelper::InjectJmpToAddress(TGalaxyNextDay, (void*)TGalaxyNextDay);
    }
}
