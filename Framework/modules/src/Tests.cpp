#include "Tests.h"
#include "Logger.h"

using namespace std;

namespace Tests 
{
    void TimeTestsStartTest(wchar_t* testname)
    {
        timetesttemp[*testname] = DateTime::TimestampMillisecond();
    }

    uint64_t TimeTestsEndTest(wchar_t* testname)
    {
        if (timetesttemp.find(*testname) == timetesttemp.end()) 
        {
            Logger::WriteMessageError(L"Not find test named " + wstring(testname));
            return 0;
        }

        timetesttemp.erase(*testname);
        return DateTime::TimestampMillisecond()-timetesttemp[*testname];
    }
};