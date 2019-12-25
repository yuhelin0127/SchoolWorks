#include <stdio.h>

int member_array_c(unsigned int *array, int e, int size){
  int i;
  for(i = 0; i < size; i++){
    if(array[i] == e) return 1;
  }
  return 0;
}
