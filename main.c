/**
 * main.c
 * exmaple application
 * Author:Hunkar Ciplak, hunkarciplak@hotmail.com
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
#include "fft_radix2.h"


int main(void)
{
    complex buf[SAMPLE_BUF_SIZE] = {10 + 0*I,20 + 0*I,30 + 0*I,40 + 0*I,50 + 0*I,60 + 0*I,70 + 0*I,80 + 0*I,
                       90 + 0*I,100 + 0*I,110 + 0*I,120 + 0*I,130 + 0*I,140 + 0*I,150 + 0*I,160 + 0*I}; //input buf samples..
    complex results[SAMPLE_BUF_SIZE]; //will store fft results
    printf("********************************  FFT Calculation, radix-2 DIT  ******************************** \r\n");
    memset(results, 0, sizeof(results));
    calcul_fft_radix2(SAMPLE_BUF_SIZE, buf, results);   //SAMPLE_BUF_SIZE : number of samples
    printf("\r\n###  Input - Samples:\r\n");
    for(int i = 0; i < SAMPLE_BUF_SIZE; i++)
        printf("%d:%f %fi \r\n", i, creal(*(buf + i)), cimag(*(buf + i)));
    printf("###  FFT Results:\r\n");
    for(int i = 0; i < SAMPLE_BUF_SIZE; i++)
        printf("%d:%f %fi \r\n", i, creal(*(results + i)), cimag(*(results + i)));

    return EXIT_SUCCESS;
}
