// stm32_fir_prbs_CMSIS_intr.c

#include "stm32_wm5102_init.h"

#include "bp1750.h"

float32_t x, y, state[N];
arm_fir_instance_f32 S;

void SPI2_IRQHandler()
{	
  int16_t left_in_sample = 0;
  int16_t right_in_sample = 0;
  int16_t left_out_sample = 0;
  int16_t right_out_sample = 0;

	if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) != SET) 
    {
      left_in_sample = SPI_I2S_ReceiveData(I2Sx);
      GPIO_SetBits(GPIOD, GPIO_Pin_15);
      x = (float32_t)(prbs());
 		  arm_fir_f32(&S, &x, &y, 1);
 	    left_out_sample = (short)(y);
      GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		  while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
		  SPI_I2S_SendData(I2Sxext, left_out_sample);			
  	}
		else
    {
		  right_out_sample = SPI_I2S_ReceiveData(I2Sx);
		  while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
		  SPI_I2S_SendData(I2Sxext, right_out_sample);
	  }
}

int main(void)
{
  arm_fir_init_f32(&S,N,h,state,1);
  stm32_wm5102_init(FS_8000_HZ, WM5102_LINE_IN, IO_METHOD_INTR);
  while(1){}
}
