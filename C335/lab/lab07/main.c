/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000

#define PI 3.14159265358979323846

// declare relevant functions
float board_compass_heading(float[3]);
float pitch(float[3]);
float roll(float[3]);
float abso(float);
float max(float, float);
float min(float, float);
void drawBars(float, float, float, float, uint16_t*, uint16_t*, uint16_t*);

int main(void) {
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
   
   // invoke relevant inits
   f3d_i2c1_init();
   delay(10);
   f3d_accel_init();
   delay(10);
   f3d_mag_init();
   delay(10);

	f3d_uart_init();
	f3d_lcd_init();
	f3d_user_btn_init();

	// declare all necessary data
	float accel_data[3];
	float mag_data[3];
	
	int input = -1;
	int lastInput = -1;
	int activeScene = 0;
	
	float pitchVal  = 0.0;
	float rollVal = 0.0;
	float lastPitch = -1.0;
	float lastRoll = -1.0;
	
	// clear whatever was previously on the screen
	f3d_lcd_fillScreen(WHITE);	
	
	// an array of white colors used to clear the screen
   uint8_t y;
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
		f3d_accel_read(accel_data);
		f3d_mag_read(mag_data);
		input = user_btn_read();
		
		// if the user has pressed the button, switch the active scene
		if(input && lastInput != 1){
			activeScene++;
			activeScene %= 2;		
			f3d_lcd_fillScreen(WHITE);	
		}
		lastInput = input;
		
		// calculate the pitch and roll of the board
		pitchVal = pitch(accel_data);
		rollVal = roll(accel_data);
		
		// draw board tilt		
		if(activeScene){
			drawBars(pitchVal, rollVal, lastPitch, lastRoll, barRowRed, barRowBlue, clearRow);
		}
		// draw board heading
		else{
	     // clear previous heading
		  f3d_lcd_fillScreen(WHITE);	
        float head = board_compass_heading(mag_data);

		  // draw heading
		  draw_line(90 - head);
        printf("%f \n", head);
		  delay(10);
		}
		
		// take note of previous values so we know how many rows to clear next time the loop runs
		lastPitch = pitchVal;
		lastRoll = rollVal;
		
		// debugging
		// printf("Accelerometer data: %f, %f, %f\n", accel_data[0], accel_data[1], accel_data[2]);
		// printf("Magnetometer data: %f, %f, %f\n", mag_data[0], mag_data[1], mag_data[2]);

		// printf("%f, %f\n", pitch(accel_data), roll(accel_data));
		// printf("%f\n", board_compass_heading(mag_data));
		// printf("%f\n", board_compass_heading(mag_data));
	}
}

float board_compass_heading(float mag_data[3]){
 /* float p = pitch(mag_data);
  float r = roll(mag_data);
  
  float M1 = mag_data[0] * cos(p) + mag_data[2] * sin(p);
  float M2 = mag_data[0] * sin(r) * sin(p) + mag_data[1] * cos(r) - mag_data[2] * sin(r) * cos(p);
  
  float heading;
  
  if(M1 > 0 && M2 >= 0){
    heading = atan(M2/M1) * (180/PI);
  }
  else if(M1 < 0){
    heading = 180 + atan(M2/M1) * (180/PI);
  }
  else if(M1 > 0 && M2 <= 0){
    heading = 360 + atan(M2/M1) * (180/PI);
  }
  else if (M1 == 0 && M2 < 0){
    heading = 90;
  }
  else{
    heading = 270.0;  
  }
  printf("%f\n", atan2(mag_data[0], mag_data[1]) * (180/PI));*/
  return atan2(mag_data[1], mag_data[0]) * (180/PI);
}

// float* [3] -> float
// calculates the pitch of the board
float pitch(float data[3]){
	return atan(data[0]/(sqrt(pow(data[1], 2) + pow(data[2], 2)))) * (180/PI);
}

// float* [3] -> float
// calculates the roll of the board
float roll(float data[3]){
	return atan(data[1]/sqrt(pow(data[0], 2) + pow(data[2], 2))) * (180/PI);
}

// float -> float
// returns the absolute value of the input float
float abso(float f){
	if(f < 0){
		return f * -1.0;
	}
	else{
	return f;
	}
}

// float, float -> float
// returns the largest of the two inputs
float max(float f1, float f2){
	if(f1 > f2){
		return f1;
	}
	else{
		return f2;
	}
}

// float, float -> float
// returns the smaller of the two inputs
float min(float f1, float f2){
	if(f1 < f2){
		return f1;
	}
	else{
		return f2;
	}
}

// draw the bars for float and pitch
// uint16_t*, uint16_t*, uint16_t* -> void
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

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

