#include "tt.h"
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <errno.h> */
/* #include <math.h> */

float exponential(float x, int n)
{
    float sum = 1.0f; // initialize sum of series
 
    int i = n - 1;
    for (; i > 0; --i )
        sum = 1 + x * sum / i;
 
    return sum;
}

float distortion(float x, int n){
    /* return x; */
    float y;
    float factor = 2.0;
    if(x > 0){
        y = 1 - exponential(-x, n);
        /* y = 1 - exp(-x); */
    } else {
        y = -1 + exponential(x, n);
        /* y = -1 + exp(x); */
    }

    y /= factor;
    return y;
}

float absolute(float val){
    if(val >= 0)
        return val;
    else
        return -1 * val;
}

float waveshaper(float x_n, float drive){
    float factor = 25.0;
    x_n /= factor;
    float y = (((1 + drive) * x_n) / (1 + drive * absolute(x_n)));
    return y;
}

float foldback(float in, float threshold){
    /* fprintf(stderr, "%.4f\n", in); */
    /* printf("foldback: %.4f\n", in); */
    if (in > threshold || in < -threshold){
        in = fabs(fabs(fmod(in - threshold, threshold * 4)) - threshold * 2) - threshold;
    }
    return in;
}

// Place the audio processing algorithm here. The input and output are given
// as unsigned integer pointers.
void processBlock(unsigned int *block_ptr)
{
    int i;
    /* float temp_out; */
    float sample;	

    //Clear the Block Ready Semaphore
    blockReady = 0;
    
    //Set the Processing Active Semaphore before starting processing
    isProcessing = 1;

    /* FILE* fp = fopen("./output.txt", "w+"); */
    /* fprintf(fp, "NUM_SAMPLES: %d\n", NUM_SAMPLES); */

    /* for(i=0;i<NUM_SAMPLES;i++) */
    /* { */
    int num_coeff = 3;
    float drive_k = 0.5;
    float drive = (2 * drive_k) / (1 - drive_k);
    drive = 1;
    float threshold = 5;
    for(i=0;i<NUM_SAMPLES; i++)
    {
        /* *(block_ptr+i) =  *(block_ptr+i); */
        sample = (float)(int)((*(block_ptr + i)) << 9);
        /* fprintf(stdout, "%.4f\n", sample); */
        /* printf("%.4f\n", sample); */
        sample = distortion(sample, num_coeff);
        /* sample = waveshaper(sample, drive); */
        sample = foldback(sample, threshold);
        *(block_ptr + i) = (unsigned)(((int)sample) >> 9);
    }

    //Clear the Processing Active Semaphore after processing is complete
    /* fclose(fp); */
    isProcessing = 0;
}
