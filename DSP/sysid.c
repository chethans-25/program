// stm32f4_sysid_CMSIS_intr.c

#include "stm32f4_wm5102_init.h"

#define BLOCK_SIZE 1
#define NUM_TAPS 128

float32_t beta = 1E-12;
float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
float32_t firCoeffs32[NUM_TAPS] = { 0.0f };
arm_lms_instance_f32 S;
float32_t yn, adapt_in, adapt_out, adapt_err,input,wn;

void SPI2_IRQHandler()
{	
  int16_t lis = 0;
  int16_t ris = 0;
  int16_t los = 0;
  int16_t ros = 0;

  if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) == SET) 
    {
  	    lis = SPI_I2S_ReceiveData(I2Sx);
	    input = (float32_t)(lis);
		adapt_in = (float32_t)(prbs(8000));
        los = (int16_t)(adapt_in);
		while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
		SPI_I2S_SendData(I2Sxext, los);			
        GPIO_SetBits(GPIOD, GPIO_Pin_15);
		arm_lms_f32(&S, &adapt_in, &input, &adapt_out, &adapt_err, BLOCK_SIZE);	
        GPIO_ResetBits(GPIOD, GPIO_Pin_15);
  	}
		else
    {
		  ris = SPI_I2S_ReceiveData(I2Sx);
		  ros = 0;
		  while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
		  SPI_I2S_SendData(I2Sxext, ros);
	}
}

int main(void)
{
  arm_lms_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], beta, BLOCK_SIZE);
  stm32_wm5102_init(FS_8000_HZ, WM5102_LINE_IN, IO_METHOD_INTR);
  while(1){}
}
