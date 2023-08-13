// PAM Modulation & Demodulation
//Include A/D to D/A Codec header file
#include "DSK6416_aic23.h"
//Choose the sampling rate. The sampling rate can be increased upto 96 KHz. For e.g., 48KHz sampling
//rate, fs=DSK6416_AIC23_FREQ_48KHZ
Uint32 fs=DSK6416_AIC23_FREQ_8KHZ;
//The default setting for line_IN or mic_IN
#define DSK6416_AIC23_INPUT_LINE 0x0011
// Select either Line_IN or Mic_IN for giving an input signal
Uint16 inputsource=DSK6416_AIC23_INPUT_LINE; // select input as Line input.

#include <math.h>


//Initialization:
int i_M, j_M;
int i_D, j_D;
int k;
int masked_value, demod_level, buffer, initial, output, assign, bit;
int data_PAM[4];
short mode=2;


interrupt void c_int11() //interrupt service routine
{
int sample_data;
switch(mode)
{
case 1:
{
//4-PAM Modulator: Assigns sampled data coming from an input
//source to 4 predetermined voltage levels.
if (i_M==96) //new input is taken once every 96 samples (8 shifts x 12 repeated outputs)
{
sample_data = input_sample(); //inputs data
i_M=0;
j_M=0;
}
masked_value = sample_data & 0x0003; //masks input sample as 2-bit segments
output = data_PAM[masked_value]; //gets corresponding level from table
output_sample(output);
//outputs corresponding voltage level 12 times
j_M++;
//repeated output counter
if (j_M==12)
{
j_M=0;
sample_data = sample_data >> 2; //shifts input to mask next segment
}
i_M++;
break;
}
//--------------------------------------------------------------------------------
case 2:
{
//4-PAM Demodulator
sample_data = input_sample(); //inputs data
buffer=0;
//initializing buffer
for (j_D=0; j_D<8; j_D++)
{
masked_value = sample_data & 0x0003; //masks input sample as 2-bit segments
output = data_PAM[masked_value]; //retrieves the corresponding hex value from data table
sample_data = sample_data >> 2; //shifts input so as to mask another part on the next cycle
demod_level = (initial - output)/(0x5555); //determines which level was transmitted by doing
//inverse operation to modulator
demod_level = demod_level << 14; //aligns constructed value since least significant bits are first
//extracted
buffer = buffer + demod_level; //adds bit pattern just recovered to previously formed output sample
buffer = buffer >> 2; //creates vacancy for bits coming next
}
output_sample(buffer*16); //adjusts output voltage level
break;
}
}
return;
}



void main()
{
initial=0x7FFF;
for(k=0; k<4; k++)
{
assign = initial-(k*0x5555);
data_PAM[k] = assign;
}
i_M=96;
comm_intr();
//init DSK, codec, McBSP
while(1); //infinite loop
}