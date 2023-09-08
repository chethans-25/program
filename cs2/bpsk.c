//BPSK – C Code
//Include A/D to D/A Codec header file
#include "DSK6416_aic23.h"
//Choose the sampling rate. The sampling rate can be increased upto 96 KHz. For e.g., 48KHz
//sampling rate, fs=DSK6416_AIC23_FREQ_48KHZ
Uint32 fs=DSK6416_AIC23_FREQ_8KHZ;
//The default setting for line_IN or mic_IN
#define DSK6416_AIC23_INPUT_LINE 0x0011
// Select either Line_IN or Mic_IN for giving an input signal
Uint16 inputsource=DSK6416_AIC23_INPUT_LINE; // select input as Line input.
//If the input is given in Mic than, Uint16 inputsource=DSK6416_AIC23_INPUT_MIC;
#include <math.h>
//Initialization:
int i_M, j_M;
int i_D, j_D;
int k;
int masked_value, demod_level, buffer, initial, output, assign, bit;
int temp[4];
//mode=1 for modulation and mode=2 for demodulation
short mode=1;
//Data table for PSK MOD & DEMOD:
int data[2][4]={0, 1000, 0, -1000, //0 degree
0, -1000, 0, 1000}; //180 degree
interrupt void c_int11() //interrupt service routine
{
int sample_data;
switch(mode)
{
case 1:
{
//Modulation
if (i_M==64) //Use this PSK
{
sample_data = input_sample(); //inputs data
i_M=0;
j_M=0;
}
masked_value = sample_data& 0x0001;
output = data[masked_value][j_M]; //gets level from table
output_sample(output*10); //outputs sinusoid
j_M++; //repeated output counter
if (j_M==4) // Use this for PSK //checks if 1-bit segment was output
{
j_M=0;
sample_data = sample_data>> 1;
}
i_M++;
break;
}
//----------------------------------------------------------------------------------------------
case 2:
{
// Demodulation
sample_data = input_sample(); //inputs data
buffer=0;
for (i_D=0; i_D<16; i_D++)
{
for (j_D=0; j_D<4; j_D++) // 4 data_table bits
{
masked_value = sample_data& 0x0001; // input sample
output = data[masked_value][j_D];
temp[j_D]=output; //temp holds modulated value
}
bit=0; //initializes bit to its default value
//demodulation starts
if (temp[1]==-1000) // Use this for PSK //checks the 2nd value in temp array and determines
//if corresponding bit is 1 or 0
{
bit = 1;
}
bit = bit << 15; // aligns determined bit to right location
buffer = buffer + bit;
if (i_D!=15) // prevents redundant shifting
buffer = buffer >> 1;
sample_data = sample_data>> 1 ;
}
output_sample(buffer);
break;
}
}
return;
}
void main()
{
//BPSK Modulator:
i_M=64, j_M=0;
comm_intr();
//init DSK, codec, McBSP
while(1);
//infinite loop
}