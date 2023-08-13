//QPSK- C Code
//Modulation and demodulation QPSK
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
//Data table for QPSK MOD & DEMOD:
int data[4][4]={0, 1000, 0, -1000, //phase=0 & symbol=00
1000, 0, -1000, 0, //phase=90 & symbol=01
0,-1000, 0, 1000, //phase=270 & symbol=10
-1000, 0, 1000,0}; //phase=180 & symbol=11
interrupt void c_int11() //interrupt
service routine
{
int sample_data;
switch(mode)
{
case 1:
{
// Modulation
if (i_M==32)
{
sample_data = input_sample(); //inputs data
i_M=0;
j_M=0;
}
masked_value = sample_data& 0x0003;
output = data[masked_value][j_M]; //gets level from table
output_sample(output*10); //outputs sinusoid
j_M++; //repeated output counter
if (j_M==4) // checks if 1-bit segment was output
{
j_M=0;
sample_data = sample_data>> 2;
}
i_M++;
break;
}
//--------------------------------------------------------------------------------------------------------
case 2:
{
//Demodulation
sample_data = input_sample(); //inputs data
buffer=0;
for (i_D=0; i_D<8; i_D++)
{
for (j_D=0; j_D<4; j_D++)
{
masked_value = sample_data& 0x0003;
output = data[masked_value][j_D];
temp[j_D]=output; //temp holds modulated value
}
bit=0; //initializes bit to its default value
//demodulation starts
if (temp[0]==0)
{
if (temp[1]==-1000)
bit=3;
} //checks first 2 values and determines corresponding bit
else
{
if (temp[0]==1000)
bit=1;
else
bit=2;
}
bit = bit << 14; // aligns determined bit to right location
buffer = buffer + bit;
if (i_D!=7)
buffer = buffer >> 2;
sample_data = sample_data>> 2; //shifts input so as to another part
}
output_sample(buffer);
break;
}
}
return;
}
void main()
{
i_M=32, j_M=0;
comm_intr();
//init DSK, codec, McBSP
while(1);
//infinite loop
}