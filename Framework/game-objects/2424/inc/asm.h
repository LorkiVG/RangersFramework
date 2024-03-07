#pragma once
#define ASM_CALL(fun, arg1, arg2)  _asm \
{                                       \
    _asm push eax                      \
    _asm mov eax, arg1                 \
    _asm push edx                       \
    _asm mov edx, arg2                  \
    _asm call fun                       \
    _asm pop edx                        \
    _asm pop eax                        \
}