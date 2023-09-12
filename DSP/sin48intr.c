// stm32f4_sine48_intr.c 

#include "stm32f4_wm5102_init.h"

#define LOOPLENGTH 48
int16_t sine_table[LOOPLENGTH] = {0, 1305, 2588, 3827, 5000, 6088, 7071, 7934, 8660, 9239, 9659, 9914, 10000,
                                9914, 9659, 9239, 8660, 7934, 7071, 6088, 5000, 3827,  2588, 1305,
                                0,-1305,-2588,-3827,-5000,-6088,-7071,-7934,-8660, -9239, -9659, -9914, -10000,
                                -9914, -9659, -9239, -8660, -7934, -7071, -6088, -5000, -3827, -2588, -1305};
int16_t sine_ptr = 0;  // pointer into lookup table

void SPI2_IRQHandler()
{	
  int16_t los, ros;
  int16_t lis, ris;

  if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) == SET) 
  {
	lis = SPI_I2S_ReceiveData(I2Sx);
    los = sine_table[sine_ptr];
    sine_ptr = (sine_ptr+1)%LOOPLENGTH;
    while(SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
    SPI_I2S_SendData(I2Sxext, los);			
  }
  else
  {
    ris = SPI_I2S_ReceiveData(I2Sx);
    ros = 0;
    while(SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
    SPI_I2S_SendData(I2Sxext, ros);
  }
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
 }

int main(void)
{
  stm32_wm5102_init(FS_48000_HZ, WM5102_LINE_IN, IO_METHOD_INTR);
  while(1){}
}
