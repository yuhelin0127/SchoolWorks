
/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMER 20000
#define AUDIOBUFSIZE 128
#define PI 3.141592653


extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

FATFS Fatfs;		/* File system object */
FIL fid;		/* File object */
BYTE Buff[512];		/* File read buffer */
int ret;

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;      
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd))
    exit(-1);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
}

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

int if_pressed(uint8_t y, uint8_t c, uint8_t z) {
  if(y == 255 || y == 0 || c == 1 || z==1) {
    return 1;
  }
  else return 0;
}

void draw_character1(int x, int y) {
  char head[10] = " 0 ";
  char body[10] = "/|\\$";
  char leg[10] =  "/ \\";

  f3d_lcd_drawString(x, y, head,BLACK,WHITE);
  f3d_lcd_drawString(x, y+8,body,BLACK,WHITE);
  f3d_lcd_drawString(x, y+16,leg,BLACK,WHITE);
}

void draw_character2(int x, int y) {
  char head[10] = " 0 ";
  char body[10] = "/|\\*";
  char leg[10] =  "/ \\";

  f3d_lcd_drawString(x, y, head,BLACK,WHITE);
  f3d_lcd_drawString(x, y+8,body,BLACK,WHITE);
  f3d_lcd_drawString(x, y+16,leg,BLACK,WHITE);
}

void clean_character(int x, int y) {
  char head[10] = " 0 ";
  char body[10] = "/|\\$";
  char leg[10] =  "/ \\";

  f3d_lcd_drawString(x, y, head,WHITE,WHITE);
  f3d_lcd_drawString(x, y+8,body,WHITE,WHITE);
  f3d_lcd_drawString(x, y+16,leg,WHITE,WHITE);
}

void draw_start_scene(){
  
  char title[64] = "SHOOT & DIE";
  
  char line1[35] = " _  _________.------.";
  char line2[35] = "  \\`'  _______|_____|";
  char line3[35] = "  /   (_)__]";
  char line4[35] = " |    |";
  char line5[35] = ".'   .'";
  char line6[35] = "|____]";
  
  char instruc1[30] = "PRESS USER BUTTON";
  char instruc2[30] = "TO START THE GAME";
  
  f3d_lcd_drawString(30, 30,  title,  BLACK,WHITE);
  
  f3d_lcd_drawString(0, 52,  line1,  BLACK,WHITE);
  f3d_lcd_drawString(0, 60,  line2,  BLACK,WHITE);
  f3d_lcd_drawString(0, 68, line3,  BLACK,WHITE);
  f3d_lcd_drawString(0, 76, line4,  BLACK,WHITE);
  f3d_lcd_drawString(0, 84, line5,  BLACK,WHITE);
  f3d_lcd_drawString(0, 92,  line6,  BLACK,WHITE);

  f3d_lcd_drawString(15, 115, instruc1,BLACK,WHITE);
  f3d_lcd_drawString(15, 123, instruc2,BLACK,WHITE);
}

void draw_player1_win_scene(){
  char player1_win[15] = "Player 1 wins";
  f3d_lcd_drawString(30, 80, player1_win,BLACK,WHITE);
}

float pitch(float data[3]){
  return atan(data[0]/(sqrt(pow(data[1], 2) + pow(data[2], 2)))) * (180/PI);
}

void draw_player2_win_scene(){
  char player2_win[15] = "Player 2 wins";
  f3d_lcd_drawString(30, 80, player2_win,BLACK,WHITE);
}

void shoot_bullet1(uint8_t x, uint8_t y) {
  if(y > 95 || y < 65) {
    f3d_lcd_drawPixel(x,y-1,BLUE);
    f3d_lcd_drawPixel(x,y,WHITE);
    delay(5);
  }
}

void shoot_bullet2(uint8_t x, uint8_t y) {
  if(y > 95 || y < 65) {
    f3d_lcd_drawPixel(x,y+1,BLUE);
    f3d_lcd_drawPixel(x,y,WHITE);
    delay(5);
  }
}



int main(void) { 

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;
  int bytesread;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  //initialization
  f3d_i2c1_init();  
  f3d_uart_init();
  f3d_timer2_init();
  f3d_dac_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_user_btn_init();
  f3d_led_init();
  f3d_lcd_init();
  f3d_accel_init();
  
  f3d_nunchuk_init();
  delay(100);
  nunchuk_t nunc; 

  int scene = 0;
  int player1_health = 3;
  int player2_health = 3;
  int x1 = 100;
  int y1 = 100;
  int x2 = 30;
  int y2 = 30;
  int x_acc = 2;
  int y_acc = 2;
  int bullet_x1 = 0;
  int bullet_y1 = 0;
  int bullet_x2 = 0;
  int bullet_y2 = 0;
  int if_bullet_exist1 = 0;
  int if_bullet_exist2 = 0;
  char press;
  players_health_led(player1_health, player2_health);
  f3d_lcd_fillScreen2(WHITE);  
  float accel[3];

  while(1) {
    f3d_accel_read(accel);
    float g = pitch(accel);
    f3d_nunchuk_read(&nunc);
    //f_mount(0, &Fatfs);
    if (scene == 0){
      draw_start_scene();
      //rc = f_open(&fid, "500hz-16.wav", FA_READ);
      if(user_btn_read()){
	draw_UI();
	scene = 1;
      }
    }
    if (scene == 1){
      if(nunc.jy == 0) {
	clean_character(x1,y1);
	y1 = y1 + y_acc;
	if(y1 >= 135) y1 = 135;
	draw_character1(x1,y1);
	y_acc = y_acc >= 6 ? 6 : y_acc + 1;
      } else if (nunc.jy == 255) { 
	clean_character(x1,y1);
	y1 = y1 - y_acc;
	if(y1 <= 98) y1 = 98;
	draw_character1(x1,y1);
	y_acc = y_acc >= 6 ? 6 : y_acc + 1;
      } else {
	y_acc = 2;
      }
      if(nunc.jx == 0) {
	clean_character(x1,y1);
	x1 = x1 - 2;
	if(x1 <= 5) x1 = 5;
	draw_character1(x1,y1);
	x_acc = x_acc >= 7 ? 7 : x_acc + 1;
	//When joystick goes up or c pressed, switch to previous song and update.
      } else if (nunc.jx == 255) { 
	clean_character(x1,y1);
	x1 = x1 + 2;
	if(x1 >= 100) x1 = 100;
	draw_character1(x1,y1);
	x_acc = x_acc >= 7 ? 7 : x_acc + 1;
      } else {
	x_acc = 2;
      }// End of player1
      
      press = getchar();
      
      if (press == 'w') { 
	clean_character(x2,y2);
	y2 = y2 - 5;
	if(y2 <= 0) y2 = 0;
	draw_character2(x2,y2);
      } 

      if(press == 's') {
	clean_character(x2,y2);
	y2 = y2 + 5;
	if(y2 >= 42) y2 = 42;
	draw_character2(x2,y2);
      }

      if(press == 'a') {
	clean_character(x2,y2);
	x2 = x2 - 2;
	if(x2 <= 5) x2 = 5;
	draw_character2(x2,y2);
      } 
     
      if (press == 'd') { 
	clean_character(x2,y2);
	x2 = x2 + 2;
	if(x2 >= 100) x2 = 100;
	draw_character2(x2,y2);
      }// End of player2

      if(nunc.z == 1 && if_bullet_exist1 == 0) {
	bullet_x1 = x1 + 20;
	bullet_y1 = y1 + 6;
	shoot_bullet1(bullet_x1, bullet_y1);
	if_bullet_exist1 = 1;
      }
      
      if(bullet_y1 <= 0) {
	if_bullet_exist1 = 0;
      } else if(if_bullet_exist1 == 1) {
	bullet_y1 -= 1;
	shoot_bullet1(bullet_x1, bullet_y1);
      }
	  
	  
      if(bullet_y1 <= y2 + 12 && (bullet_x1 >= x2 && bullet_x1 <= x2 + 18) && if_bullet_exist1 == 1){
	if_bullet_exist1 = 0;
	player2_health -= 1;
        players_health_led(player1_health, player2_health);
      }// Hit player2
      // End of player1 shooting
      
    
      if(press == 'z' && if_bullet_exist2 == 0) {
	bullet_x2 = x2 + 20;
	bullet_y2 = y2 + 6;
	shoot_bullet2(bullet_x2, bullet_y2);
	if_bullet_exist2 = 1;
      }
      
      if(bullet_y2 >= 180) {
	if_bullet_exist2 = 0;
      } else if(if_bullet_exist2 == 1) {
	bullet_y2 += 1;
	shoot_bullet2(bullet_x2, bullet_y2);
      }
	  
	  
      if(bullet_y2 >= y1 + 8 && (bullet_x2 >= x1 && bullet_x2 <= x1 + 18) && if_bullet_exist2 == 1){
	if_bullet_exist2 = 0;
	player1_health -= 1;
	players_health_led(player1_health, player2_health);
      }// Hit player1
      // End of player2 shooting

      if(g > 30 || g < -30) {
	player1_health = 3;
        player2_health = 3;
        players_health_led(player1_health, player2_health);
      }
     
    }

    if(player2_health <= 0 && scene == 1){
      f3d_lcd_fillScreen2(WHITE);
      draw_player1_win_scene();
      scene = 2;
    }

    if(player1_health <= 0 && scene == 1){
      f3d_lcd_fillScreen2(WHITE);
      draw_player2_win_scene();
      scene = 2;
    }

    


    if(scene == 2){
      if(user_btn_read()){
	f3d_lcd_fillScreen2(WHITE);
	scene = 0;
	player1_health = 3;
        player2_health = 3;
        players_health_led(player1_health, player2_health);
      }
    }

    /* if (!rc) {
  struct ckhd hd;
  uint32_t  waveid;
  struct fmtck fck;
    
  readckhd(&fid, &hd, 'FFIR');
    
  f_read(&fid, &waveid, sizeof(waveid), &ret);
  if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
    return -1;
    
    readckhd(&fid, &hd, ' tmf');
    
    f_read(&fid, &fck, sizeof(fck), &ret);
    
    // skip over extra info
    
    if (hd.cksize != 16) {
      printf("extra header info %d\n", hd.cksize - 16);
      f_lseek(&fid, hd.cksize - 16);
    }
    
    printf("audio format 0x%x\n", fck.wFormatTag);
    printf("channels %d\n", fck.nChannels);
    printf("sample rate %d\n", fck.nSamplesPerSec);
    printf("data rate %d\n", fck.nAvgBytesPerSec);
    printf("block alignment %d\n", fck.nBlockAlign);
    printf("bits per sample %d\n", fck.wBitsPerSample);
    
    // now skip all non-data chunks !
    
    while(1){
      readckhd(&fid, &hd, 0);
      if (hd.ckID == 'atad')
	break;
      f_lseek(&fid, hd.cksize);
    }
    
    printf("Samples %d\n", hd.cksize);
    
    // Play it !
    
    // audioplayerInit(fck.nSamplesPerSec);
   
    f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
    hd.cksize -= ret;
    audioplayerStart();
    while (hd.cksize) {
      int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
      if (audioplayerHalf) {
	if (next < AUDIOBUFSIZE/2)
	  bzero(Audiobuf, AUDIOBUFSIZE/2);
	f_read(&fid, Audiobuf, next, &ret);
	hd.cksize -= ret;
	audioplayerHalf = 0;
      }
      if (audioplayerWhole) {
	if (next < AUDIOBUFSIZE/2)
	  bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
	f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
	hd.cksize -= ret;
	audioplayerWhole = 0;
      }
    }
    audioplayerStop();
  }
  
    printf("\nClose the file.\n"); 
    rc = f_close(&fid);
    if (rc) die(rc);
    */

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
