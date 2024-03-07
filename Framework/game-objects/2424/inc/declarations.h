#pragma once
#include <cstdint>
#include <windows.h>

#define byte     std::uint8_t
#define word     std::uint16_t
#define dword    std::uint32_t

// Indicates areas without data in structures
#define empty8    std::int8_t
#define empty16    std::int16_t
#define empty32    std::int32_t
#define empty64    std::int64_t

// Indicates that ints are not yet marked up in the decompilation process
#define unkint8     std::int8_t
#define unkint16    std::int16_t
#define unkint32    std::int32_t
#define unkint64    std::int64_t

#define unkuint8     std::uint8_t
#define unkuint16    std::uint16_t
#define unkuint32    std::uint32_t
#define unkuint64    std::uint64_t

// Indicates that floats are not yet marked up in the decompilation process
#define unkfloat    float
#define unkdouble   double

#define PTR      void*
#define UNKPTR   void*
#define UNK      dword

#define STR      wchar_t*
#define WSTR     wchar_t*


// Indicates that bytes are not yet marked up in the decompilation process
#define _gap_8   std::uint8_t
#define _gap_16  std::uint16_t
#define _gap_32  std::uint32_t
#define _gap     std::uint8_t

#define FUNC     void*
#define METHOD   void*

#ifndef NOT_IDA
    #define HANDLE_ HANDLE
#else
    #define HANDLE_ dword
#endif

struct _pair_byte {
    byte x;
    byte y;
};

struct _pair_int {
    int x;
    int y;
};

struct _pair_float {
    float x;
    float y;
};

struct _pair_double {
    double x;
    double y;
};