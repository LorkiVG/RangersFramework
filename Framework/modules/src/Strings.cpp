#include "Strings.h"

namespace Strings 
{
    wchar_t *ltrim(wchar_t *s)
    {
        while(isspace(*s)) s++;
        return s;
    }
    wchar_t *rtrim(wchar_t *s)
    {
        wchar_t* back = s + wcslen(s);
        while(isspace(*--back));
        *(back+1) = '\0';
        return s;
    }
    __forceinline wchar_t* trim(wchar_t* s) {rtrim(ltrim(s));}

    wstring ltrimwstr(const wstring &s) {
        return regex_replace(s, wregex(L"^\\s+"), wstring(L""));
    }

    wstring rtrimwstr(const wstring &s) {
        return regex_replace(s, wregex(L"\\s+$"), wstring(L""));
    }
    __forceinline wstring trimwstr(wstring s) {rtrimwstr(ltrimwstr(s));}


    wchar_t* SubString(const wchar_t* str, uint32_t start, uint32_t end)
    {
        uint32_t outStrLen = end - start;

        //Alloc memory for output string
        wchar_t* outStr = (wchar_t*)malloc(sizeof(wchar_t) * (outStrLen + 1));
        //Loop until the string length ends or the string end
        for (int i = start; i < end && (*(str + i) != '\0'); i++)
        {
            *outStr = *(str + i);
            outStr++;
        }
        *outStr = '\0';
        return outStr - outStrLen;
    }
    __forceinline wstring SubString(wstring str, uint32_t m, uint32_t n)
    {
        return str.substr(m,n);
    }

    wchar_t* Reverse(wchar_t* str)
    {
        uint32_t len=wcslen(str);
        uint32_t n=len-1;
        uint32_t i;
        
        for(i = 0; i <=(len>>1); i++)
        {
            swap(str[i],str[n]);
            n--;
        }
        return str;
    }
    wstring Reverse(wstring str)
    {
        uint32_t len = str.length();
        uint32_t n = len-1;
        uint32_t i = 0;

        for(i = 0; i <= (len>>1); i++)
        {
            swap(str[i],str[n]);
            n--;
        }
        return str;
    }

    uint32_t CountSymbol(wchar_t* str, wchar_t* symbol)
    {
        uint32_t a = 0;
        uint32_t n = 0;
        uint32_t len = wcslen(str);
        while(n != len) {
            if (str[n] == symbol[0]) a++;
            n++;
        }
        return a;
    }
    
    uint32_t CountSymbol(wstring str, wstring symbol)
    {
        uint32_t a = 0;
        uint32_t n = 0;
        uint32_t len = str.length();
        while(n != len) {
            if (str[n] == symbol[0]) a++;
            n++;
        }
        return a;
    }


    uint32_t CountStr(wchar_t* str, wchar_t* word)
    {
        uint32_t a = 0;
        uint32_t n = 0;
        uint32_t len = wcslen(str)-1;
        uint32_t lenw = wcslen(word)-1;
        uint32_t bufl = 0;
        while(n != len) {
            if (str[n] == word[bufl]) {
                if (bufl == lenw) {
                    bufl = 0;
                    a++;
                }
                else {
                    bufl++;
                }
            }
            else {
                bufl = 0;
            }
            n++;
        }
        return a;
    }
    
    uint32_t CountStr(wstring str,wstring word)
    {
        uint32_t a = 0;
        uint32_t n = 0;
        uint32_t len = str.length()-1;
        uint32_t lenw = word.length()-1;
        uint32_t bufl = 0;
        while(n != len) {
            if (str[n] == word[bufl]) {
                if (bufl == lenw) {
                    bufl = 0;
                    a++;
                }
                else {
                    bufl++;
                }
            }
            else {
                bufl = 0;
            }
            n++;
        }
        return a;
    }
    
    

    uint32_t FindStrPos(wchar_t* str,wchar_t* word)
    {
        uint32_t n = 0;
        uint32_t len = wcslen(str)-1;
        uint32_t lenw = wcslen(word)-1;
        uint32_t bufl = 0;
        while(n != len) {
            if (str[n] == word[bufl]) {
                if (bufl == lenw) {
                    bufl = 0;
                    return n;
                }
                else {
                    bufl++;
                }
            }
            n++;
        }
    }
    
    __forceinline uint32_t FindStrPos(wstring str,wstring word)
    {
        return str.find(word);
    }

    uint32_t FindSymbolPos(wchar_t* str, wchar_t* symbol)
    {
        uint32_t n = 0;
        uint32_t len = wcslen(str)-1;
        while(n != len) {
            if (str[n] == symbol[0]) return n;
            n++;
        }
    }
    
    uint32_t FindSymbolPos(wstring str, wstring symbol)
    {
        uint32_t n = 0;
        uint32_t len = str.length()-1;
        while(n != len) {
            if (str[n] == symbol[0]) return n;
            n++;
        }
    }
    

    __forceinline wchar_t* FindStr(wchar_t* str,wchar_t* word)
    {
        return SubString(str,FindStrPos(str,word),wcslen(str)-1);
    }
    __forceinline wstring FindStr(wstring str,wstring word)
    {
        return str.substr(FindStrPos(str,word),str.length()-1);
    }
    

    wchar_t* GetParSepSymbol(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num
    )
    {
        uint32_t n = 0;
        uint32_t len = wcslen(par_string);

        uint32_t s = 0;

        uint32_t f = 0;
        while(n != len){
            
            //Checking for between separators
            if(par_string[n]==sep[0]){
                f++;
                if(f == par_num) return SubString(par_string,s,n);
                s=n;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) return SubString(par_string,s,len);
            
        }
        //If nothing is found, return an empty string
        return L"";
    }
    wstring GetParSepSymbol(
        wstring par_string,
        wstring sep,
        uint32_t par_num
    )
    {
        uint32_t n = 0;
        uint32_t len = par_string.length()-1;

        uint32_t s = 0;

        uint32_t f = 0;
        while(n != len){
            
            //Checking for between separators
            if(par_string[n]==sep[0])
            {
                f++;
                if(f == par_num) return par_string.substr(s,n);
                s=n;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) return par_string.substr(s,len);
            
        }
        //If nothing is found, return an empty string
        return L"";
    }
    

    wchar_t* GetParSepStr(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num
    )
    {
        uint32_t len = wcslen(par_string)-1;
        
        uint32_t lens = wcslen(sep)-1;
        uint32_t n = 0;

        uint32_t l = 0;
        uint32_t s = 0;

        uint32_t f = 0;
        while(n != len){
            //Checking for between separators
            if (par_string[n] == sep[l]) {
                if (l == lens) {
                    //Separator finded
                    l = 0;
                    f++;
                    if(f == par_num) return SubString(par_string,s,n);
                    s=n;
                }
                else {
                    l++;
                }
            }
            else {
                l = 0;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) return SubString(par_string,s,len);
        }
        //If nothing is found, return an empty string
        return L"";
    }
    wstring GetParSepStr(
        wstring par_string,
        wstring sep,
        uint32_t par_num
    )
    {
        uint32_t len = par_string.length()-1;
        uint32_t lens = sep.length()-1;
        uint32_t l = 0;
        uint32_t n = 0;

        uint32_t s = 0;

        uint32_t f = 0;
        while(n != len){
            //Checking for between separators
            if (par_string[n] == sep[l]) {
                if (l == lens) {
                    //Separator finded
                    l = 0;
                    f++;
                    if(f == par_num) return par_string.substr(s,n);
                    s=n;
                }
                else {
                    l++;
                }
            }
            else {
                l = 0;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) return par_string.substr(s,len);
        }
        //If nothing is found, return an empty string
        return L"";
    }

    void SetParSepSymbol(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num,
        wchar_t* newstrpar
    )
    {
        uint32_t n = 0;
        uint32_t len = wcslen(par_string)-1;

        uint32_t s = 0;

        uint32_t f = 0;
        while(n != len){
            
            //Checking for between separators
            if(par_string[n]==sep[0]) {
                f++;
                if(f == par_num) par_string = SubString(par_string,0,s)+*newstrpar+*SubString(par_string,n,len);break;
                s=n;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) par_string = SubString(par_string,0,s)+*newstrpar+*SubString(par_string,n,len);break;
            
        }
    }
    void SetParSepSymbol(
        wstring* par_string,
        wstring sep,
        uint32_t par_num,
        wstring newstrpar
    )
    {
        uint32_t n = 0;
        uint32_t len = par_string->length()-1;
        
        uint32_t s = 0;

        uint32_t f = 0;
        wstring temp = *par_string;
        while(n != len){
            
            //Checking for between separators
            if(temp[n]==sep[0]) {
                f++;
                
                if(f == par_num) {
                    temp = SubString(*par_string,0,s)+newstrpar+SubString(*par_string,n,len); 
                    free(par_string);
                    par_string = &temp;
                    break;
                }
                s=n;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) {
                temp = SubString(*par_string,0,s)+newstrpar+SubString(*par_string,n,len); 
                free(par_string);
                par_string = &temp;
                break;
            }
            
        }
    }

    void SetParSepStr(
        wchar_t* par_string,
        wchar_t* sep,
        uint32_t par_num,
        wchar_t* newstrpar
    )
    {
        uint32_t len = wcslen(par_string)-1;
        uint32_t lens = wcslen(sep)-1;
        uint32_t n = 0;
        uint32_t l = 0;
        
        uint32_t s = 0;
       
        uint32_t f = 0;
        while(n != len){
            //Search between separators
            if (par_string[n] == sep[l]) {
                if (l == lens) {
                    //Separator finded
                    l = 0;
                    f++;
                    if(f == par_num) par_string = SubString(par_string,0,s) + *newstrpar + *SubString(par_string,n,len); break;
                    s=n;
                }
                else {
                    l++;
                }
            }
            else {
                l = 0;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) par_string = SubString(par_string,0,s)+*newstrpar+*SubString(par_string,n,len);break;
        }
    }

    void SetParSepStr(
        wstring* par_string,
        wstring sep,
        uint32_t par_num,
        wstring newstrpar
    )
    {
        uint32_t len = par_string->length()-1;
        uint32_t lens = sep.length()-1;
        uint32_t n = 0;
        uint32_t l = 0;
        
        uint32_t s = 0;
        
        uint32_t f = 0;
        wstring temp = *par_string;
        while(n != len){
            //Search between separators
            if (temp[n] == sep[l]) {
                if (l == lens) {
                    //Separator finded
                    l = 0;
                    f++;
                    if(f == par_num) {
                        temp = SubString(temp,0,s)+newstrpar+SubString(temp,n,len); 
                        free(par_string);
                        par_string = &temp;
                        break;
                    }
                    s=n;
                }
                else {
                    l++;
                }
            }
            else {
                l = 0;
            }
            n++;
            //Checks if the line has ended and if a separator has been found
            if(len==n && f == par_num-1) {
                temp = SubString(temp,0,s)+newstrpar+SubString(temp,n,len); 
                free(par_string);
                par_string = &temp;
                break;
            }
        }
    }


    int32_t ConvertToInt(wchar_t* stringin)
    {
        return _wtoi(stringin);
    }
    int32_t ConvertToInt(wstring stringin)
    {
        return stoi(stringin);
    }
    double ConvertToDouble(wchar_t* stringin)
    {
        return wcstod(stringin,nullptr);
    }
    double ConvertToDouble(wstring stringin)
    {
        return stod(stringin);
    }
};