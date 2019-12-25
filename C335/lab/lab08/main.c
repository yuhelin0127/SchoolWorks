/* main.c ---
*  Team 8 
*  Name: Yuheng Lin, Griffin Halloran
*  Lab 08
/* Code: */

#include <math.h>
#include <stm32f30x.h>
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <stdio.h>

#define TIMER 20000

#define PI 3.14159265358979323846

float board_compass_heading(float[3]);
float pitch(float[3]);
float roll(float[3]);
float abso(float);
float max(float, float);
float min(float, float);
void drawBars(float, float, float, float, uint16_t*, uint16_t*, uint16_t*);

int main(void) {
  
  // init all the communicators
  f3d_uart_init();
  delay(100);
  f3d_gyro_init();
  f3d_i2c1_init();
  delay(100);
  f3d_accel_init();
  delay(100);
  f3d_mag_init();
  delay(100);
  f3d_lcd_init();
  delay(100);
  f3d_user_btn_init();
  delay(100);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  f3d_nunchuk_init();
  delay(100);
  
  f3d_lcd_fillScreen(WHITE);
  
  // declare varibles
  float accel_data[3];
  float mag_data[3];
  float axis[3];
  float nun_accel_data[3];

  nunchuk_t p;
  // define display title	
  char *One = "Board Tilt Angle";
  char *Two = "Compass Heading";
  char *Three = "Gyro Display";
  char *Four = "Nunchuck Tilt Angle";

  float pitchVal  = 0.0;
  float rollVal = 0.0;
  float pitchVal2  = 0.0;
  float rollVal2 = 0.0;
  float lastPitch = -1.0;
  float lastRoll = -1.0;
  float lastPitch2 = -1.0;
  float lastRoll2 = -1.0;

  // define the starting display
  int input = 0;
  
  uint8_t y;
  uint8_t height;
  uint16_t clearRow[15];
  for (y = 0; y < 15; y++) 
  clearRow[y] = WHITE;
     
  // arrays of red and blue colors to draw a row of the bars
  uint16_t barRowRed[15];
  uint16_t barRowBlue[15];
   
  for(y = 0; y < 15; y++){
     barRowRed[y] = RED;
     barRowBlue[y] = BLUE;
  }

   while(1){
        f3d_gyro_getdata(axis);
        f3d_accel_read(accel_data);
	f3d_mag_read(mag_data);
	f3d_nunchuk_read(&p);
        printf("jx: %u", p.jx);
	// make the displays switch circlely
	if(p.jx < 110 || (int)p.z == 1){
	  input--;
          if(input < 0){
            input = 3;
          }
        }
        if(p.jx > 150 || (int)p.c == 1){
          input++;
	  if(input > 3){
	    input = 0;
          }
	}

        switch(input){
	// draw board tilt angle
        case 1:
	  // clean previous display
          f3d_lcd_fillScreen(WHITE);
          f3d_lcd_drawString(20 , 140, One, BLACK, WHITE);
	  pitchVal = pitch(accel_data);
	  rollVal = roll(accel_data);		
	  drawBars(pitchVal, rollVal, lastPitch, lastRoll, barRowRed, barRowBlue, clearRow);
          break;
	// draw compass display
        case 2:
	  // clean previous display
	  f3d_lcd_fillScreen(WHITE);
          f3d_lcd_drawString(20 , 140, Two, BLACK, WHITE);
          float head = board_compass_heading(mag_data);
	  draw_line(90 - head);
          break;
	// draw gyro display
        case 0:
	  // clean previous display
          basic_struct();
	  f3d_lcd_drawString(30 , 140, Three, BLACK, WHITE);
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
	  break;
	// draw nunchuck tilt angle display
	case 3:
	  // clean previous display
	  f3d_lcd_fillScreen(WHITE);
          f3d_lcd_drawString(10, 140, Four, BLACK, WHITE);
          // get nunchuck accelerometer axis
          nun_accel_data[0] = (float)p.ax;
          nun_accel_data[1] = (float)p.ay;
          nun_accel_data[2] = (float)p.az;          
          pitchVal2 = pitch(nun_accel_data);
	  rollVal2 = roll(nun_accel_data);		
	  drawBars(pitchVal2, rollVal2, lastPitch2, lastRoll2, barRowRed, barRowBlue, clearRow);
	  break;
	default:
	  break;
	}
		
	// take note of previous values so we know how many rows to clear next time the loop runs
	lastPitch = pitchVal;
	lastRoll = rollVal;
	lastPitch2 = pitchVal2;
	lastRoll2 = rollVal2;        
        
        delay(100);
	}
}

void drawBars(float pitchVal, float rollVal, float lastPitch, float lastRoll, uint16_t* barRowRed, uint16_t* barRowBlue, uint16_t* clearRow){
	int n, i;
			
	// clear previous bars
   for(i = 0; i < 5 + abso(abso(rollVal) - abso(lastRoll)); i++){
 		f3d_lcd_setAddrWindow (5, min(abso(rollVal), abso(lastRoll)) + i,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
 		f3d_lcd_pushColor(clearRow, 15);
  	}			
	for(i = 0; i < 5 + abso(abso(pitchVal) - abso(lastPitch)); i++){
 		f3d_lcd_setAddrWindow (80, min(abso(pitchVal), abso(lastPitch)) + i,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
 		f3d_lcd_pushColor(clearRow, 15);
  	}			
          
	// draw labels			
 	f3d_lcd_drawString(0, 120, "  Roll  ", BLUE, WHITE);
   f3d_lcd_drawString(75, 120, "  Pitch  ", BLUE, WHITE);			
			
	// draw pitch bar
 	for(i = 0; i < abso(rollVal); i++){
 		f3d_lcd_setAddrWindow (5, i,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
 		f3d_lcd_pushColor(rollVal > 0 ? barRowRed : barRowBlue, 15);
  	}			
			
	// draw roll bar
	for(i = 0; i < abso(pitchVal); i++){
  		f3d_lcd_setAddrWindow (80, i,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
 		f3d_lcd_pushColor(pitchVal > 0 ? barRowRed : barRowBlue, 15);
  	}
}


float board_compass_heading(float mag_data[3]){
  return atan2(mag_data[1], mag_data[0]) * (180/PI);
}

float pitch(float data[3]){
  return atan(data[0]/(sqrt(pow(data[1], 2) + pow(data[2], 2)))) * (180/PI);
}

float roll(float data[3]){
  return atan(data[1]/sqrt(pow(data[0], 2) + pow(data[2], 2))) * (180/PI);
}

float abso(float f){
	if(f < 0){
		return f * -1.0;
	}
	else{
	return f;
	}
}

float min(float f1, float f2){
	if(f1 < f2){
		return f1;
	}
	else{
		return f2;
	}
}


float max(float f1, float f2){
	if(f1 > f2){
		return f1;
	}
	else{
		return f2;
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

