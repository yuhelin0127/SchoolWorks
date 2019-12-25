

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
  f3d_systick_init();
  f3d_lcd_init();
  
  
  
  char title[12] = "Song player";
  char nameOne[15] = "Thermo.wav";
  char nameTwo[15] = "500hz-16.wav";
  char arrow[3] = "->";
  int boo = 0;
  int y = 15;
  f3d_lcd_fillScreen(WHITE);
  f3d_lcd_drawString(30, 0, title, BLUE, WHITE);
  f3d_lcd_drawString(10, 15, arrow, RED, WHITE);
  f3d_lcd_drawString(30, 15, nameOne, BLACK, WHITE);
  f3d_lcd_drawString(30, 30, nameTwo, BLACK, WHITE);
  f3d_lcd_drawString(30, 45, nameOne, BLACK, WHITE);
  
   printf("Hello World21331231\n");

   f3d_nunchuk_init();
   delay(100);
    nunchuk_t nunc; 
  
   while(1) {
    f3d_nunchuk_read(&nunc);
    //When joystick goes down or z pressed, switch to next song and update UI. 
    if(nunc.jy == 0 || nunc.z == 1) {
      f3d_lcd_drawString(10, y, arrow, WHITE, WHITE);
      y = y + 15;
      if(y > 45) y = 15;
      f3d_lcd_drawString(10, y, arrow, RED, WHITE);
      //When joystick goes up or c pressed, switch to previous song and update.
    } else if (nunc.jy == 255 || nunc.c == 1) { 
      f3d_lcd_drawString(10, y, arrow, WHITE, WHITE);
      y = y - 15;
      if(y < 15) y = 45;
      f3d_lcd_drawString(10, y, arrow, RED, WHITE);
    }
    f_mount(0, &Fatfs);// Register volume work area
    //switch case to open different songs.
    
    delay(400);
    
    switch(y) {
    case 15:
      printf("Open Thermo.wav\n");
      //rc = f_open(&fid, "thermo.wav", FA_READ);
      rc = f_open(&fid, "thermo.wav", FA_READ);
      
      break;
    case 30:
      printf("Open 500hz-16.wav\n");
      //rc = f_open(&fid, "TD.wav", FA_READ);
      rc = f_open(&fid, "500hz-16.wav", FA_READ);
      break;
    case 45:
      printf("Open Thermo\n");
      rc = f_open(&fid, "thermo.wav", FA_READ);
      break;
    }
    
    
    if (!rc) {
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
    int x = if_pressed(nunc.jy,nunc.c,nunc.z);
    while (hd.cksize) {
      x = if_pressed(nunc.jy,nunc.c,nunc.z);
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
