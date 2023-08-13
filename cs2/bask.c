#include "DSK6416_aic23.h"
Uint32 fs=DSK6416_AIC23_FREQ_8KHZ;
#define DSK6416_AIC23_INPUT_LINE 0x0011
//#define DSK6416_AIC23_INPUT_MIC 0x0015
Uint32 sample_data;
Uint16 inputsource=DSK6416_AIC23_INPUT_LINE; // select input
#include<math.h>//Initialization:
int i_ASK_M, i_ASK_D;
int j_ASK_M, j_ASK_D;
int k;
int masked_value, demod_level, buffer, initial, output, assign, bit;
int temp[4];
short mode=1;
//Data table for ASK MOD & DEMOD:
int data_ASK[2][4]={0,0,0,0,0, -1000, 0, 1000};
interrupt void c_int11() //interrupt service routine
{
int sample_data;
switch(mode)
{
//-------------------------------------------------------------------------------------------------
case 1:
{
//ASK Modulator
if (i_ASK_M==64) //determines when to get new input
{
sample_data = input_sample(); //inputs data
i_ASK_M=0;
j_ASK_M=0;
}
masked_value = sample_data& 0x0001; //masks input sample
output = data_ASK[masked_value][j_ASK_M]; //gets level from table
output_sample(output*10); //outputs sinusoid
j_ASK_M++; //repeated output counter
if (j_ASK_M==4) //checks if 1-bit segment was output
{
j_ASK_M=0;
sample_data = sample_data>> 1;//shifts input mask another part
}
i_ASK_M++; break;
}
case 2:
{
//ASK Demodulator
sample_data = input_sample(); //inputs data
buffer=0;
for (i_ASK_D=0; i_ASK_D<16; i_ASK_D++)//counting 16
{
for (j_ASK_D=0; j_ASK_D<4; j_ASK_D++) // 4 data_table bits
{
masked_value = sample_data& 0x0001;// input sample
output = data_ASK[masked_value][j_ASK_D];
temp[j_ASK_D]=output; //temp holds modulated value
}
bit=0; //initializes bit to its default value
//demodulation starts
if (temp[1]==-1000) //checks the 2nd value in temp array and
{
//determines if corresponding bit is 1 or 0
bit = 1;
}
bit = bit << 15; //aligns determined bit to right location
buffer = buffer + bit;
if (i_ASK_D!=15) //prevents redundant shifting
buffer = buffer >> 1;
sample_data = sample_data>> 1; //shifts input so as to mask another part
}
output_sample(buffer);
break;
}
//-------------------------------------------------------------------------------------------------
}
return;
}
void main()
{
//ASK Modulator:
i_ASK_M=64;
j_ASK_M=0;
comm_intr(); //init DSK, codec, McBSP
while(1); //infinite loop
}