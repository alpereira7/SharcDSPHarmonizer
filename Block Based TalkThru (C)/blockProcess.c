#include "tt.h"
#include <stdio.h>

// Place the audio processing algorith here. The input and output are given
// as unsigned integer pointers.
void processBlock(unsigned int *block_ptr)
{
    int i;
    float temp_out;

    //Clear the Block Ready Semaphore
    blockReady = 0;
    
    //Set the Processing Active Semaphore before starting processing
    isProcessing = 1;

    for(i=0;i<NUM_SAMPLES;i++)
    {
       *(block_ptr+i) =  *(block_ptr+i);
       // *(block_ptr+i) = 0;
       // unsigned int curr_val = *(block_ptr + i);
       // printf("current_value: %u\n", curr_val);
    }

    //Clear the Processing Active Semaphore after processing is complete
    isProcessing = 0;
}
