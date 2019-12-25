//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>


int main(void){

  f3d_uart_init();
  f3d_user_btn_init();
  f3d_led_init();
  int led = 0;
  int i;
  while(1){
    f3d_led_on(led);
    if(user_btn_read()){
      for (i = 0; i < 100; i++){
	printf("!!!!!!\n");
      }
    }
    f3d_led_off(led);
    if(led != 7){
      led++;
    }
    else{
      f3d_led_all_off();
      led = 0;
    }
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
