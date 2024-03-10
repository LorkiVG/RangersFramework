#include "Path.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"

using namespace std;

namespace Logger 
{
    void Write(wstring str_out)
    {
        wofstream f(Path::logPath, ios::app);
        f << str_out << L"\n";
        f.close();
    }
    void WriteChar(char* str_out)
    {
        FILE* file = fopen(Path::logPath_char, "a");
        fprintf(file, "%s\n", str_out);
        fclose(file);
    }
    void WriteChar(const char* str_out)
    {
        FILE* file = fopen(Path::logPath_char, "a");
        fprintf(file, "%s\n", str_out);
        fclose(file);
    }
    void WriteBinary(char* data)
    {
        FILE* file = fopen(Path::logPath_char, "ab");
        size_t dataSize = sizeof(data) / sizeof(data[0]);
        size_t elementsWritten = fwrite(data, 1, dataSize, file);
    }
    void WriteMessage(wstring str_out)
    {
        Logger::Write(L"VG Framework " + str_out);
    }
    void WriteMessageError(wstring str_out)
    {
        Logger::WriteMessage(L"Error! " + str_out);
    }
    void WriteMessageWarning(wstring str_out)
    {
        Logger::WriteMessage(L"Warning! " + str_out);
    }
}