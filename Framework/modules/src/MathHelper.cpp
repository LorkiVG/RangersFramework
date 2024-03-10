#include "MathHelper.h"

namespace MathM {
    const int FastMultiplyByBytes(int a, int b)
    {
        return a << b;
    }
    const int FastSplitByBytes(int a, int b)
    {
        return a >> b;
    }
    const int isPrime(uint32_t num) 
    {
        if (num == 2) return true;
        if (!(num & 1)) return false;
        double sqrt_num = sqrt(double(num));
        for (int div = 3; div <= sqrt_num; div += 2) 
        {
            if (num % div == 0) return false;
        }
        return true;
    }
    double PartInRange(
        double cur,
        double a,
        double b,
        double fromA,
        double toB
    )
    {
        if (a < b)
        {
            if (cur <= a) return fromA;
            else if (cur >= b) return toB;
            else return (cur - a) / (b - a) * (toB - fromA) + fromA;
        }
        else
        {
            if (cur >= a) return fromA;
            else if (cur <= b) return toB;
            else return (a - cur) / (a - b) * (toB - fromA) + fromA;
        }
    }
    int BankRound(double value)
    {
        float fShift = (value >= 0 ? 0.5 : -0.5);
        //    
        if (fabs(fabs(value) - fabs(double(int(value))) - 0.5) < DBL_EPSILON)
        {
            //return (double(int(value / 2.0 + fShift) * 2));
            return (double(nearbyint(value * 0.5f) * 2.0f)); //   
        }
        return (double(int(value + fShift)));
    }
};