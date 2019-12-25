#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mult_by_7.h"

void mult_by_7_test(void) {
  int i;
  int error_count=0;
  for (i = 0; i <= 100; i++){
    if (mult_by_7(i) != mult_by_7_c(i)){
      printf("Mult by 7 Error: Input %d, Expected %d, Received %d\n",i,mult_by_7_c(i),mult_by_7(i));
      error_count++;
    }
  }
  if (!error_count) {
    printf("Mult by 7 Tests Passed\n");
  }
  else {
    printf("Mult by 7 Test: %d errors\n",error_count);
  }
}