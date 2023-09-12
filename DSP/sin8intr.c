// stm32f4_sine8_intr.c 

#include "stm32f4_wm5102_init.h"

#define LOOPLENGTH 8
int16_t sine_table[LOOPLENGTH] = {0, 7071, 10000, 7071, 0, -7071, -10000, -7071};
int16_t sine_ptr = 0;  // pointer into lookup table

void SPI2_IRQHandler()
{	
  int16_t left_out_sample, right_out_sample;
  int16_t left_in_sample, right_in_sample;

  if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) == SET) 
  {
		left_in_sample = SPI_I2S_ReceiveData(I2Sx);
    left_out_sample = sine_table[sine_ptr];
    sine_ptr = (sine_ptr+1)%LOOPLENGTH;
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
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
 }

int main(void)
{
  stm32_wm5102_init(FS_8000_HZ, 
	                  WM5102_LINE_IN,
	                  IO_METHOD_INTR);
  while(1){}
}
