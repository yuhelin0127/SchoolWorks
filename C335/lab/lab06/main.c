// Zicheng Wang
// zicwang
// Yuheng Lin
// yuhelin

#include <stm32f30x.h>   // Pull in include files for F30x standard drivers
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  f3d_lcd_init();
  f3d_lcd_fillScreen2(RED);
  f3d_gyro_init();

  float axis[3];
  uint8_t height;
  printf("Hello\n");

  while (1) {
    

    f3d_gyro_getdata(axis);
    basic_struct();
   
    printf("x: %f \n", axis[0]);
    printf("y: %f \n", axis[1]);
    printf("z: %f \n", axis[2]);

    if(axis[0] < 0) {
      axis[0] = axis[0] * (-1);
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[0]);
      draw_upper_block(15, height);
    }
    else {
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[0]);
      draw_down_block(15, height);
    }
    if(axis[1] < 0) {
      axis[1] = axis[1] * (-1);
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[1]);
      draw_upper_block((ST7735_width / 2 -5), height);
    }
    else {
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[1]);
      draw_down_block((ST7735_width / 2 -5), height);
    }
    if(axis[2] < 0) {
      axis[2] = axis[2] * (-1);
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[2]);
      draw_upper_block((ST7735_width -25), height);
    }
    else {
      height = (uint8_t)(((ST7735_height-40) / 2) + 30 + axis[2]);
      draw_down_block((ST7735_width -25), height); 
    }
   
    delay(1000);
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
