/* main.c --- 
 *
 * Filename: main.c
 * Description: Basic C program to print out hello world! 
 * Author: Adeel Bhutta
 *
*/

#include <stdio.h>
#include <unistd.h>

int main(void) {
  printf("Hello, Weclome to Spring2018\\C291\n");
  int n = 9;
  while(n < 10) {
  printf(".\n");
  sleep(1);
  }

  return(0); 
}


