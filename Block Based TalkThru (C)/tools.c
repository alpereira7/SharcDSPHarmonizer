#include "tools.h"

float absolute(float val){
	return (val >= 0) ? val : -val;
}

float exponential(float x, int n)
{
    float sum = 1.0f; // initialize sum of series
 
    int i = n - 1;
    for (; i > 0; --i )
        sum = 1 + x * sum / i;
 
    return sum;
}
