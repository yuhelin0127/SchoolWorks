// Will Smith
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_lcd_sd.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <math.h>
#include <diskio.h>
#include <stdio.h>
#include "bmp.h"

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */

struct bmpfile_magic magic;
struct bmpfile_header header;
BITMAPINFOHEADER info;
struct bmppixel pixel;

uint16_t sixteenBitColor(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t rval = r >> 3;
  uint8_t gval = g >> 2;
  uint8_t bval = b >> 3;
  return ((bval << 11) | (gval << 5) | (rval));
}
uint16_t eightBitColor(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t rval = r >> 6;
  uint8_t gval = g >> 5;
  uint8_t bval = b >> 5;
  return ((bval << 13) | (gval << 8) | (rval << 3));
}

int printImage(int imageNumber, int direction, int eightBitColorMode) {
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;

  f_mount(0, &Fatfs);		/* Register volume work area (never fails) */

  printf("\nOpen an existing file.\n");
  char imageName[12];
  if (imageNumber == 1) strcpy(imageName, "IMAGE01.BMP");
  if (imageNumber == 2) strcpy(imageName, "IMAGE02.BMP");
  if (imageNumber == 3) strcpy(imageName, "IMAGE03.BMP");
  rc = f_open(&Fil, imageName, FA_READ);
  if (rc) die(rc);

  rc = f_read(&Fil, &magic, 2, &br);
  printf("Magic %c%c\n", magic.magic[0], magic.magic[1]);
  if (rc) die(rc);

  rc = f_read(&Fil, &header, sizeof(header), &br);
  printf("Header filesize %d  offset %d\n", header.filesz, header.bmp_offset);
  if (rc) die(rc);
  
  rc = f_read(&Fil, &info, sizeof(info), &br);
  printf("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
  if (rc) die(rc);

  f3d_lcd_fillScreen(BLACK);
  if (direction == 0 && info.height < info.width) {
   int x, y;
   for (y=0; y<160; y++) {
     for (x=159; x>=0; x--) {
       rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
       if (rc) die(rc);
       if (x < info.height && y < info.height) {
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(x,y,color);
       }
     }
   }
  }
  else if (direction == 0 && info.height > info.width) {
   int x, y;
   for (y=0; y<160; y++) {
     for (x=0; x<160; x++) {
       if (x < info.width && y < info.width) {
         rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
         if (rc) die(rc);
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(x,y,color);
       }
     }
   }
  }
  else if (direction == 1 && info.height < info.width) {
   int x, y;
   for (y=0; y<160; y++) {
     for (x=159; x>=0; x--) {
         rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
         if (rc) die(rc);
       if (x < info.height && y < info.height) {
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(y,x,color);
       }
     }
   }
  }
  else if (direction == 1 && info.height > info.width) {
   int x, y;
   for (y=0; y<160; y++) {
     for (x=0; x<160; x++) {
       if (x < info.width && y < info.width) {
       rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
       if (rc) die(rc);
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(y,x,color);
       }
     }
   }
  }
  else if (direction == 2 && info.height < info.width) {
   int x, y;
   for (y=159; y>=0; y--) {
     for (x=159; x>=0; x--) {
       rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
       if (rc) die(rc);
       if (x < info.height && y < info.height) {
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(x,y,color);
       }
     }
   }
  }
  else if (direction == 2 && info.height > info.width) {
   int x, y;
   for (y=159; y>=0; y--) {
     for (x=0; x<160; x++) {
       if (x < info.width && y < info.width) {
         rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
         if (rc) die(rc);
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(x,y,color);
       }
     }
   }
  }
  else if (direction == 3 && info.height < info.width) {
   int x, y;
   for (y=159; y>=0; y--) {
     for (x=159; x>=0; x--) {
         rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
         if (rc) die(rc);
       if (x < info.height && y < info.height) {
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(y,x,color);
       }
     }
   }
  }
  else if (direction == 3 && info.height > info.width) {
   int x, y;
   for (y=159; y>=0; y--) {
     for (x=0; x<160; x++) {
       if (x < info.width && y < info.width) {
       rc = f_read(&Fil, &pixel, sizeof(pixel), &br);
       if (rc) die(rc);
         uint16_t color = (eightBitColorMode) ? eightBitColor(pixel.r, pixel.g, pixel.b) : sixteenBitColor(pixel.r, pixel.g, pixel.b);
         f3d_lcd_drawPixel(y,x,color);
       }
     }
   }
  }

  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
}

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_delay_init();
  delay(10);
  f3d_rtc_init();
  delay(10);
  f3d_uart_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_gyro_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);

  int currImage = 1;
  int direction = 0;
  int curr = 0;
  int eightBitColorMode = 0;
  float accel[3] = {0, 0, 0};

  struct nunchuk_data data;
  while (1) {
    f3d_nunchuk_read(&data);
    f3d_accel_read(accel);
    if (data.c || data.z) {
      eightBitColorMode = 1 - eightBitColorMode;
      printImage(currImage, direction, eightBitColorMode);
    }
    else if (data.ax > 1000 || data.jx < 5) {
      currImage--;
      if (currImage == 0) currImage = 3;
      printImage(currImage, direction, eightBitColorMode);
    }
    else if (data.ax < 50 || data.jx > 250) {
      currImage++;
      if (currImage == 4) currImage = 1;
      printImage(currImage, direction, eightBitColorMode);
    }
    else {
      if (accel[0] >= 1) curr = 0;
      else if (accel[0] <= -1) curr = 2;
      else if (accel[1] >= 1) curr = 1;
      else if (accel[1] <= -1) curr = 3;
      if (curr != direction) {
        direction = curr;
        printImage(currImage, direction, eightBitColorMode);
      }
    }
    delay(100);
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
