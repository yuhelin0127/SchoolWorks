#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "member_array.h"

void member_array_test(void) {
  int error_count=0;
  int size = 2;
  int e = 3;
  unsigned int list[] = {1,2,3,4};
  if(member_array(list, e, size) != member_array_c(list, e, size)){
    error_count++;
    printf("Member Array error: recieved %d, expected  %d\n",member_array(list, e, size), member_array_c(list, e, size));
  }
  if (!error_count) {
    printf("Member Array Tests Passed\n");
  }
  else {
    printf("Member Array Test: %d errors\n",error_count);
  }
}
