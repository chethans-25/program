// stm32f4_sine_intr.c
#include “stm32f4_wm5102_init.h”
#define SAMPLING_FREQ 8000
float32_t frequency = 1000.0;
float32_t amplitude = 10000.0;
float32_t theta_increment;
float32_t theta = 0.0;
void SPI2_IRQHandler()
{
int16_t left_out_sample, right_out_sample;
int16_t left_in_sample, right_in_sample;
if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) SET)
{
left_in_sample = SPI_I2S_ReceiveData(I2Sx);
theta_increment = 2*PI*frequency/SAMPLING_FREQ;
theta += theta_increment;
if (theta > 2*PI) theta -= 2*PI;
GPIO_SetBits(GPIOD, GPIO_Pin_15);
left_out_sample = (int16_t)(amplitude*sinf(theta));
GPIO_ResetBits(GPIOD, GPIO_Pin_15);
while(SPI_I2S_GetFlagStatus(I2Sxext,
SPI_I2S_FLAG_TXE ) != SET){}
SPI_I2S_SendData(I2Sxext, left_out_sample);
}
else
{
right_in_sample = SPI_I2S_ReceiveData(I2Sx);
right_out_sample = 0;
while(SPI_I2S_GetFlagStatus(I2Sxext,
SPI_I2S_FLAG_TXE ) != SET){}
SPI_I2S_SendData(I2Sxext, right_out_sample);
}
}
int main(void)
{
stm32_wm5102_init(FS_8000_HZ,
WM5102_LINE_IN,
IO_METHOD_INTR);
while(1){}
}