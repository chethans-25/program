// stm32_fir_prbs_intr.c

#include "stm32_wm5102_init.h"


#include "bp1750.h"

float32_t x[N];
int16_t k = 0;

void SPI2_IRQHandler()
{	
  int16_t left_in_sample = 0;
  int16_t right_in_sample = 0;
  int16_t left_out_sample = 0;
  int16_t right_out_sample = 0;
  short i;
  float32_t yn = 0.0;

  if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) == SET) 
    {
      left_in_sample = SPI_I2S_ReceiveData(I2Sx);
      GPIO_SetBits(GPIOD, GPIO_Pin_15);
      x[k++] = (float32_t)(prbs());
      if (k >= N) k = 0;
      for (i=0 ; i<N ; i++)
      {
				yn += h[i]*x[k++];
				if (k >= N) k = 0;
		  }
 	    left_out_sample = (short)(yn);
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
  stm32_wm5102_init(FS_8000_HZ, WM5102_LINE_IN, IO_METHOD_INTR);
  while(1){}
}
