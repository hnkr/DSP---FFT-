# Fast Fourier Transform - Radix-2
- Complex FFT
- Radix-2 Decimation in Time algorithm

## Requirements
- Ubuntu OS
- gcc

## Compile & Run
- Compile:
    - gcc fft_radix2.c main.c -o fft_radix2 -lm
- Run:
    - ./fft_radix2

## Working Principle
- It uses hardcoded sample_buf as the input / source to the FFT calculation.By default, all the imaginary part of samples are zero which is also called as real-fft.
- You only need to change the values of "buf" in main.c and  the value of "SAMPLE_BUF_SIZE" in fft_radix2.h to update sample count.
- It does not do padding automatically so you should pay attention to send an input source whose length is power-of-two.

When it starts running, firstly it writes the input source / samples and the results after calculation completed.
<br>
********************************  FFT Calculation, radix-2 DIT  ******************************** <br>
<br>
###  Input - Samples:<br>
0:10.000000 0.000000i <br>
1:20.000000 0.000000i <br>
2:30.000000 0.000000i <br>
3:40.000000 0.000000i <br>
4:50.000000 0.000000i <br>
5:60.000000 0.000000i <br>
6:70.000000 0.000000i <br>
7:80.000000 0.000000i <br>
8:90.000000 0.000000i <br>
9:100.000000 0.000000i <br>
10:110.000000 0.000000i <br>
11:120.000000 0.000000i <br>
12:130.000000 0.000000i <br>
13:140.000000 0.000000i <br>
14:150.000000 0.000000i <br>
15:160.000000 0.000000i <br>
###  FFT Results:<br>
0:1360.000000 0.000000i <br>
1:-80.000000 402.187159i <br>
2:-80.000000 193.137085i <br>
3:-80.000000 119.728461i <br>
4:-80.000000 80.000000i <br>
5:-80.000000 53.454291i <br>
6:-80.000000 33.137085i <br>
7:-80.000000 15.912989i <br>
8:-80.000000 0.000000i <br>
9:-80.000000 -15.912989i <br>
10:-80.000000 -33.137085i <br>
11:-80.000000 -53.454291i <br>
12:-80.000000 -80.000000i <br>
13:-80.000000 -119.728461i <br>
14:-80.000000 -193.137085i <br>
15:-80.000000 -402.187159i <br>





