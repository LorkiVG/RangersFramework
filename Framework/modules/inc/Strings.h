#pragma once
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

namespace Strings {
    wchar_t *ltrim(wchar_t *s);
    wchar_t *rtrim(wchar_t *s);
    __forceinline wchar_t* trim(wchar_t* s);

    wstring ltrimwstr(const wstring &s);

    wstring rtrimwstr(const wstring &s);
    __forceinline wstring trimwstr(wstring s);

    wchar_t* SubString(const wchar_t* str, uint32_t m, uint32_t n);
    __forceinline wstring SubString(wstring str, uint32_t m, uint32_t n);

    wchar_t* Reverse(wchar_t* str);
    wstring Reverse(wstring str);

    uint32_t CountSymbol(wchar_t* str, wchar_t* symbol);
    
    uint32_t CountSymbol(wstring str, wstring symbol);

    uint32_t CountStr(wchar_t* str, wchar_t* word);
    uint32_t CountStr(wstring str,wstring word);
    
    uint32_t FindSymbolPos(wchar_t* str, wchar_t* symbol);
    
    uint32_t FindSymbolPos(wstring str, wstring symbol);
    
    uint32_t FindStrPos(wchar_t* str,wchar_t* word);
    __forceinline uint32_t FindStrPos(wstring str,wstring word);

    
    __forceinline wchar_t* FindStr(wchar_t* str,wchar_t* word);
    __forceinline wstring FindStr(wstring str,wstring word);

    wchar_t* GetParSepSymbol(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num
    );
    wstring GetParSepSymbol(
        wstring par_string,
        wstring sep,
        uint32_t par_num
    );
    
    wchar_t* GetParSepStr(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num
    );
    wstring GetParSepStr(
        wstring par_string,
        wstring sep,
        uint32_t par_num
    );

    void SetParSepSymbol(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num,
        wchar_t* newstrpar
    );
    void SetParSepSymbol(
        wstring* par_string,
        wstring sep,
        uint32_t par_num,
        wstring newstrpar
    );

    void SetParSepStr(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num,
        wchar_t* newstrpar
    );

    void SetParSepStr(
        wstring* par_string,
        wstring sep,
        uint32_t par_num,
        wstring newstrpar
    );

    int32_t ConvertToInt(wchar_t* stringin);
    int32_t ConvertToInt(wstring stringin);
    double ConvertToDouble(wchar_t* stringin);
    double ConvertToDouble(wstring stringin);
};