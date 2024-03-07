#pragma once
#include "VMT.h"

struct TObjectSE {
    VMT cls;

    _gap_32 _04;
    _gap_32 _08;
    _gap_32 _0C;
    _gap_32 _10;
    _gap_32 _14;
    STR type;
    _gap_32 _1C;
    _gap_32 _20;
    _gap_32 _24;
    _gap_32 _28;
    STR _2C;
    STR _30;
    _gap_32 _34;
    PTR _38;  // TSoundBufferControl
    _gap_32 _3C;
    _gap_32 _40;
    _gap_32 _44;
    _gap_32 _48;
};