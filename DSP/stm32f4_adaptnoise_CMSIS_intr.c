// stm32f4_adaptnoise_intr.c

#include "stm32f4_wm5102_init.h"

#define SAMPLING_FREQ 8000
#define NOISE_FREQ 1200.0
#define SIGNAL_FREQ 2500.0
#define NOISE_AMPLITUDE 8000.0
#define SIGNAL_AMPLITUDE 8000.0

#define BETA 1E-12         // adaptive learning rate      
#define NUM_TAPS 10        // number of weights
#define BLOCK_SIZE 1

float32_t theta_increment_noise;
float32_t theta_noise = 0.0;
float32_t theta_increment_signal;
float32_t theta_signal = 0.0;
float32_t yout, error, signal, signoise, sigplusnoise, refnoise;


float32_t firStateF32[BLOCK_SIZE + NUM_TAPS -1];
float32_t firCoeffs32[NUM_TAPS] = {0.0};
arm_lms_instance_f32 S;

// interrupt service routine called every time a 16-bit sample
// is received via I2S, i.e. called twice per sampling instant
// once for left channel and once for right channel
void SPI2_IRQHandler()
{	
  int16_t left_out_sample, right_out_sample;
  int16_t left_in_sample, right_in_sample;
 
  if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) == SET) 
    {
  	  left_in_sample = SPI_I2S_ReceiveData(I2Sx); // input sample not used

      GPIO_SetBits(GPIOD, GPIO_Pin_15);           // algorithm timing
      theta_increment_noise = 2*PI*NOISE_FREQ/SAMPLING_FREQ;
      theta_noise += theta_increment_noise;
      if (theta_noise > 2*PI) theta_noise -= 2*PI;
      theta_increment_signal = 2*PI*SIGNAL_FREQ/SAMPLING_FREQ;
      theta_signal += theta_increment_signal;
      if (theta_signal > 2*PI) theta_signal -= 2*PI;

      refnoise = (NOISE_AMPLITUDE*arm_cos_f32(theta_noise));  
      signoise = (NOISE_AMPLITUDE*arm_sin_f32(theta_noise));
      signal = (SIGNAL_AMPLITUDE*arm_sin_f32(theta_signal));
      sigplusnoise = signoise+signal;
	
      arm_lms_f32(&S, &refnoise, &sigplusnoise, &yout, &error, 1);
	    GPIO_ResetBits(GPIOD, GPIO_Pin_15);
      left_out_sample = ((int16_t)(error));  
			
		  while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
		  SPI_I2S_SendData(I2Sxext, left_out_sample);			
		}	
		else
    {
		  right_in_sample = SPI_I2S_ReceiveData(I2Sx);
      right_out_sample = (int16_t)(sigplusnoise);
		  while (SPI_I2S_GetFlagStatus(I2Sxext, SPI_I2S_FLAG_TXE ) != SET){}
			SPI_I2S_SendData(I2Sxext, right_out_sample);
	  }
}

int main(void)
{
  arm_lms_init_f32(&S, NUM_TAPS, firCoeffs32, firStateF32, BETA, 1);
  stm32_wm5102_init(FS_8000_HZ, WM5102_LINE_IN, IO_METHOD_INTR);
  while(1){}

}
