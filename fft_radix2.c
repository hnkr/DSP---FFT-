
/**
 * fft_radix2.c
 * Author:Hunkar Ciplak, hunkarciplak@hotmail.com
 */

#include "fft_radix2.h"
#include <complex.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



/**
 * Calculates the power/ exponent according to the base of 2.
 * sample_n_:number of samples
 * ret_val= 0:failure, >0:power of two
 */
__uint8_t get_power_of_two(__uint16_t sample_n_)
{
    __uint8_t power_of_two = 0;
    //calculate how many powers is the cnt_ of 2?
    __int32_t temp_cnt_ = sample_n_;
    while(temp_cnt_ > 1){
        if(!(temp_cnt_ % 2)){
            temp_cnt_ = temp_cnt_ / 2;
            power_of_two++;
            //printf("power_of_two:%d\r\n", power_of_two);
        }else return 0;
    }
    return power_of_two;
}



/**
 * do the bit-reversal operation and fills the start vector in the buf_.
 * cnt_:Element count 
 * buf_: Addr ın the memory to store the start vector determined after the bit-reversal operation
 * ret_val: 0=failure, 1:done.
 */
int get_start_vector(__uint16_t cnt_,  __uint16_t *buf_)
{
    __uint8_t power_of_two = get_power_of_two(cnt_);
    if(!power_of_two) return 0; //invalid count..
    power_of_two -= 1; //bit0 of the number can be shifted left at most for power_of_two - 1 times. 
    for(__uint32_t i = 0; i < cnt_; i++){
        for(__uint32_t bits = 0; bits <= 15; bits++ ){
            if(i & (1 << bits))
                buf_[i] |= (1 << (power_of_two - bits));
        }
    }
    for(__uint32_t i = 0; i < cnt_; i++)
        //printf("%d:%d\r\n", i, buf_[i]);
    return 1;
}

/**
 * Calculates the complex fft according to the radix-2.
 * sample_cnt_: sample count
 * samples_:source buf
 * res_buf: buf to store fft results
 * ret_val= 0:failure, 1:success
 */
__uint8_t calcul_fft_radix2(__uint16_t sample_cnt_,  complex *samples_,  complex *res_buf)
{
    __uint8_t gc, mcog, stepc, stepi, jumpi;
     complex *step_buf;
    __uint16_t *first_buf = calloc(sample_cnt_, sizeof(__uint16_t));
    __uint16_t array_offset, array_index, prev_array_offset, prev_array_index;
    double_t rad_consant, temp_cos_val, temp_sin_val;
    complex WN;
    if(sample_cnt_ < 2) return 0;

    stepc = get_power_of_two(sample_cnt_);  //step count in butterfly.
    
    step_buf = ( complex *)calloc(sample_cnt_ * (stepc + 1), sizeof( complex)); // + 1 due to having samples in the 1st column
    if(NULL == step_buf)
        return 0;
    get_start_vector(sample_cnt_, first_buf);   //get index of first step
    for(int i = 0; i < sample_cnt_; i++)
        step_buf[i] = samples_[first_buf[i]];  //copy the samples into the buffer,that will be used for calculatio, in the order of start vector.
    free(first_buf);
    for(stepi = 0;  stepi < stepc; stepi++){
        jumpi = pow((double)2, (double)stepi);
        mcog = jumpi * 2;
        gc =  sample_cnt_ / mcog;
        array_offset = (stepi + 1) * sample_cnt_;
        prev_array_offset = stepi * sample_cnt_;
        rad_consant = (double_t)TWO_TIMES_OF_PI / (double_t)mcog;
        for(__uint16_t gi = 0; gi < gc; gi++){
            array_index = array_offset + gi * mcog;
            prev_array_index = prev_array_offset + gi * mcog;
            for(__uint16_t mci = 0; mci < mcog / 2 ; mci++){
                temp_cos_val = cos(rad_consant * (double_t)mci);
                temp_sin_val = sin(rad_consant * (double_t)mci);
                WN = temp_cos_val - temp_sin_val * I;
                step_buf[array_index + mci] = step_buf[prev_array_index + mci] + WN * step_buf[prev_array_index + mci + jumpi];
            }
            for(__uint16_t mci = mcog / 2; mci < mcog; mci++){
                temp_cos_val = cos(rad_consant * ((double_t)mci - (double_t)(mcog / 2)));
                temp_sin_val = sin(rad_consant * ((double_t)mci - (double_t)(mcog / 2)));
                WN = temp_cos_val - temp_sin_val * I;
                step_buf[array_index + mci] = step_buf[prev_array_index + mci - jumpi] - WN * step_buf[prev_array_index + mci];
            }
        }
    }
    memmove(res_buf, step_buf + array_index, sample_cnt_ * sizeof(complex));//copy the result buf before freeing it.
    free(step_buf);
    return 1;
}


