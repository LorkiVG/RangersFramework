#pragma once
#include <string>
#include "DateTime.h"
#include <unordered_map>

namespace Tests 
{
    std::unordered_map<wchar_t, uint64_t> timetesttemp;

    void TimeTestsStartTest(wchar_t* testname);
    uint64_t TimeTestsEndTest(wchar_t* testname);
};