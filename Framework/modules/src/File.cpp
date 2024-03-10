#include "File.h"
#include "Path.h"
#include "Logger.h"

using namespace std;

namespace File 
{
    void Rename(wchar_t* oldfilename,wchar_t* newfilename) 
    {
        _wrename(oldfilename, newfilename);           
    }
    inline bool FileExists(const wstring& name) 
    {
        if (FILE* file = _wfopen(name.c_str(), L"r")) 
        {
            fclose(file);
            return true;
        }
        else 
        {
            return false;
        }
    }
    wchar_t* GetParFromFile(
        wchar_t* txt_path,
        wchar_t* param_name
    )
    {
        wstring cur_line;
        wstring path = Path::documentsPath;
        path += L"\\" + *txt_path; 
        wifstream file(path, ios::in);  
        if (file)
        { 
            int check = 0;
            while (getline(file, cur_line))
            {
                int sep = cur_line.find(L"=");
                if (cur_line.substr(0, sep) == param_name)
                {
                    cur_line = cur_line.substr(sep + 1);
                    check = 1;
                    
                    return ((wchar_t*)&cur_line);
                }
            } 
            if (!check) return ((wchar_t*)L"");
            file.close();
        }
        else return 0;
    }

    wstring GetParFromFile(
        wstring txt_path,
        wstring param_name
    )
    {
        wstring cur_line;
        wstring path = Path::documentsPath + txt_path;

        wifstream file(path, ios::in);

        if (file)
        {
            int check = 0;
            while (getline(file, cur_line))
            {
                int sep = cur_line.find(L"=");
                if (cur_line.substr(0, sep) == param_name)
                {
                    cur_line = cur_line.substr(sep + 1);
                    check = 1;
   
                    return (cur_line);
                }
            }


            if (!check) return (L"");

            file.close();
        }

        else return 0;
    }

    wchar_t* SetParFromFile(
        wchar_t* txt_path,
        wchar_t* param_name,
        wchar_t* value
    )
    {
        wstring cur_line;
        wstring add_line;
        wstring path = Path::documentsPath;
        path += L"\\" + *txt_path;

        wifstream file(path, ios::in);
        wstring old_value = L"";

        if (file)
        { 
            int check = 0;
            while (getline(file, cur_line))
            {
                int sep = cur_line.find(L"=");

                if (cur_line.substr(0, sep) == param_name)
                {
                    old_value = cur_line.substr(sep + 1);

                    if (add_line != L"") add_line += L"\n";
                    add_line += *param_name + L"=" + *value;
                    check = 1;
                }
                
                else
                {
                    if (add_line != L"") add_line += L"\n";
                    add_line += cur_line;
                }
            }
   
            if (!check)
            {
                if (add_line != L"") add_line += L"\n";
                add_line += *param_name + L"=" + *value;
            }

            file.close();
        }
  
        else add_line = *param_name + L"=" + *value;

        wofstream file_add(path, ios::out);

        file_add << add_line;
 
        file_add.close();

        if (old_value != L"") return ((wchar_t*)&old_value);
        else return ((wchar_t*)L"");
    }
};