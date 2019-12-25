//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){

  // initiate gyro, uart, btn, and led
  f3d_gyro_init();
  f3d_uart_init();
  f3d_user_btn_init();
  f3d_led_init();
  
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  float Vector3[3];
  int axis = 0;
  char c;
  
  while(1){
	  while(user_btn_read()){
	  delay();
	  if(axis >= 2) axis = 0;
	  else axis = axis + 1;
	}
	c = getChar();
	if (c == 'x') axis = 0;
	else if (c=='y') axis = 1;
	else if (c=='z') axis = 2;
	f3d_gyro_getdata(Vector3);
	f3d_led_all_off();
	
	// Start lighting the north led for values greater than 5 dgps
	// The idea is that the leds will act as a type of bar graph
	// Positive values should light the western side of the led 
	// circle and negative values should light the eastern side
	if (Vector3[axis]>5 && Vector3[axis]<=10) f3d_led_on(0);
	else if (Vector3[axis]>10 && Vector3[axis]<=15) f3d_led_on(7);
	else if (Vector3[axis]>15 && Vector3[axis]<=20) f3d_led_on(6);
	else if (Vector3[axis]>20 && Vector3[axis]<=25) f3d_led_on(5);
	else if (Vector3[axis]>25) f3d_led_on(4);
	else if (Vector3[axis]>0 && Vector3[axis]<=5) f3d_led_on(1);
	else if (Vector3[axis]>-5 && Vector3[axis]<=0) f3d_led_on(2);
	else if (Vector3[axis]<=-5) f3d_led_on(3);
	
	delay();
	if (axis==0) printf("x : %f\n",Vector3[0]);
	else if (axis==1) printf("y : %f\n",Vector3[1]);
	else if (axis==2) printf("z : %f\n",Vector3[2]);
  }
  return 0;
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
