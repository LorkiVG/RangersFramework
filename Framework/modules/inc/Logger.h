#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace Logger 
{
    void Write(std::wstring str_out);
    void WriteChar(char* str_out);
    void WriteChar(const char* str_out);
    void WriteBinary(char* data);

    void WriteMessage(std::wstring str_out);

    void WriteMessageError(std::wstring str_out);

    void WriteMessageWarning(std::wstring str_out);
}