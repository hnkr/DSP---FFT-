/**
 * fft_radix2.c
 * Author:Hunkar Ciplak, hunkarciplak@hotmail.com
 */

#ifndef _FFT_RADIX2__

#define _FFT_RADIX2__

#include <stdio.h>
#include <complex.h>

#define TWO_TIMES_OF_PI         6.283185307179 //2 x pi
#define SAMPLE_BUF_SIZE         16  //number of samples, hence outputs..


__uint8_t get_power_of_two(__uint16_t sample_n_);
int get_start_vector(__uint16_t cnt_,  __uint16_t *buf_);
__uint8_t calcul_fft_radix2(__uint16_t sample_cnt_,  complex *samples_,  complex *res_buf);

#endif