#pragma once
#include <cmath>
#include <cfloat>
#include <cstdint>

//Быстрое округление, работает в 3-4 раза быстрее встроенных ceil,round,floor
#define _ceil(x) (x-(int)x>0)?(int)x+1:(int)x
#define _round(x) (x>0)?(int)(x+0.5):(int)(x-0.5)
#define _floor(x) (x>0)?(int)x:((int)x-x>0)?(int)x-1:(int)x

namespace MathM {
    const int FastMultiplyByBytes(int a, int b);
    const int FastSplitByBytes(int a, int b);
    const int isPrime(int num);
    double PartInRange(float cur,float a,float b, float fromA,float toB);
    int BankRound(double value);
};
namespace DoubleM 
{
    const unsigned int DoubleMultiplyInt(double a, int b);
    const unsigned int DoubleSplitInt(double a, int b);
};