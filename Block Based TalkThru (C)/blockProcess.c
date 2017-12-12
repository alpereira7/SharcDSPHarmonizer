#include "tt.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

float distortion(float x){
    float y;
    if(x > 0){
        y = 1 - exp(-x);
    } else {
        y = -1 + exp(x);
    }
    return y;
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
    for(i=0;i<NUM_SAMPLES; i++)
    {
        *(block_ptr+i) =  *(block_ptr+i);
        /* sample = (float)(int)((*(block_ptr + i)) << 8); */
        /* sample = distortion(sample); */
        /* *(block_ptr + i) = (unsigned)(((int)sample) >> 8); */
    }

    //Clear the Processing Active Semaphore after processing is complete
    /* fclose(fp); */
    isProcessing = 0;
}
