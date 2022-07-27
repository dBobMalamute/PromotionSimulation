#ifndef BOOSTINCLUDES_H
#define BOOSTINCLUDES_H
#include <tgmath.h>

template<typename T> inline T factorialFunction(T a)
{
    return tgamma(a - 1.0);
}

template<typename T> inline T errorFunction(T x)
{
    return erf(x);
}

float my_logf (float a);
float my_erfinvf (float a);

template<typename T> inline T inverseErrorFunction(T x)
{
    return my_erfinvf(x);
}



#endif // BOOSTINCLUDES_H
