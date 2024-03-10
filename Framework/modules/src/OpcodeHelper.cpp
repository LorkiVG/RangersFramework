#include "OpcodeHelper.h"

namespace OpcodeHelper
{
    /// @brief Inject jmp to address
    /// @param targetAddr Address to inject jmp
    /// @param hookAddr Address where jmp jumps
    void InjectJmpToAddress(uintptr_t targetAddr, void* hookAddr)
    {
        ptrdiff_t offset;
        DWORD oldProtect;
        //Change memory protect to readwrite
        VirtualProtect((LPVOID)targetAddr, 5, PAGE_EXECUTE_READWRITE, &oldProtect); 

        // Calculate relative offset for jmp
        offset = (ptrdiff_t)hookAddr - ((ptrdiff_t)targetAddr);
        offset = offset - sizeof(offset) - 0x1;

        // Write jmp opcode to memory
        *(unsigned char*)targetAddr = 0xE9;

        // Write relative offset to memory in little-endian format
        for (size_t i = 0; i < sizeof(offset); ++i) 
        {
            *((unsigned char*)(targetAddr)+i + 1) = (offset >> (8 * i)) & 0xFF;
        }
        
        //Change memory protect to readonly
        VirtualProtect((LPVOID)targetAddr, 5, oldProtect, &oldProtect);
    }
    /// @brief Inject call to address
    /// @param targetAddr Address to inject call
    /// @param hookAddr Address where call jumps
    void InjectCallToAddress(uintptr_t targetAddr, void* hookAddr)
    {
        DWORD oldProtect;
        //Change memory protect to readwrite
        VirtualProtect((LPVOID)targetAddr, 5, PAGE_EXECUTE_READWRITE, &oldProtect); 

        // Write call opcode to memory
        *(unsigned char*)targetAddr = 0xE8;

        // Write hookAddr to memory in little-endian format
        for (size_t i = 0; i < sizeof(hookAddr); ++i) 
        {
            *((unsigned char*)(targetAddr)+i + 1) = ((uintptr_t)hookAddr >> (8 * i)) & 0xFF;
        }
        
        //Change memory protect to readonly
        VirtualProtect((LPVOID)targetAddr, 5, oldProtect, &oldProtect);
    }
}