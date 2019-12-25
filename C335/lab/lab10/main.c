#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_lcd_sd.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_uart.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <math.h>
#include <stdio.h>
#include <f3d_user_btn.h>
#include <f3d_systick.h>
#include <queue.h>

int main(void) {
    
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_user_btn_init();
  f3d_led_init();
  f3d_systick_init();
 
  while(1){
    if(putchar(getchar()) == 'a'){
      printf("left\n");
    }
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

