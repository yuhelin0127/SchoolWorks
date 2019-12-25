#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "string_compare_n.h"

void string_compare_n_test(void) {
  int n = 4;
  char s1[15] = "abcdef";
  char s2[15] = "ABCDEF";
  if(string_compare_n(char *(s1), char *(s2), n) != string_compare_n_c(char *(s1), char *(s2), n)){
    printf("String Length error: stringLength() = %d, expected stringLength_c() = %d\n", string_compare_n(*s1, *s2, n), string_compare_n_c(*s1, *s2, n));
  }
  else{
    printf("String Length Tests Passed\n");
  }
}
