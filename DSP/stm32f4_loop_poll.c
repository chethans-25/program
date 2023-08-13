 // stm32f4_loop_poll.c

 #include “stm32f4_wm5102_init.h”

 int main(void)
 {
     int16_t left_out_sample, right_out_sample;
 int16_t left_in_sample, right_in_sample;

 stm32_wm5102_init(FS_48000_HZ, WM5102_DMIC_IN, IO_METHOD_POLL);
 while(1)
 {
 while(SPI_I2S_GetFlagStatus(I2Sx,
 SPI_I2S_FLAG_RXNE ) != SET){}
 if (SPI_I2S_GetFlagStatus(I2Sx, I2S_FLAG_CHSIDE) SET)
 {
 left_in_sample = SPI_I2S_ReceiveData(I2Sx);
 left_out_sample = left_in_sample;
 while(SPI_I2S_GetFlagStatus(I2Sxext,
 SPI_I2S_FLAG_TXE ) != SET){}
 SPI_I2S_SendData(I2Sxext, left_out_sample);
 }
 else
 {
 right_in_sample = SPI_I2S_ReceiveData(I2Sx);
 right_out_sample = right_in_sample;
 while(SPI_I2S_GetFlagStatus(I2Sxext,
 SPI_I2S_FLAG_TXE ) != SET){}
 SPI_I2S_SendData(I2Sxext, right_out_sample);
 }
 }
 }