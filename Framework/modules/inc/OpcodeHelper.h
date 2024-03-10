#pragma once
#include "windows.h"

namespace OpcodeHelper
{
    void InjectJmpToAddress(uintptr_t targetAddr, void* hookAddr);
    void InjectCallToAddress(uintptr_t targetAddr, void* hookAddr);
}