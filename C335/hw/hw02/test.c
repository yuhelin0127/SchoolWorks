#include <stdio.h>
 
extern int inc(int);
 
#define RED_COUNT 5
#define YELLOW_COUNT 2
#define GREEN_COUNT 5
 
enum light_states {RED, YELLOW, GREEN};
static int state = RED;
 
void stop_light () {
  static int state_counter = 0;
  printf("address of function state_counter is :%p\n", &state_counter);
  switch (state) {
  case RED:
  printf("RED\n");
  if (++state_counter >= RED_COUNT) {
    state_counter = 0;
    state = GREEN;
  }
  break;
 
  case GREEN:
  printf("GREEN\n");
  if (++state_counter >= GREEN_COUNT) {
    state_counter = 0;
    state = YELLOW;
  }
  break;
 
  case YELLOW:
  printf("YELLOW\n");
  if (++state_counter >= YELLOW_COUNT) {
    state_counter = 0;
    state = RED;
  }
  break;
 
  default:
    state = RED;
    state_counter = 0;
    break;
  }
}
 
main(){
  int i = 0;
  printf("address of function state is :%p\n", &state);
  printf("address of function stop_light() is :%p\n", &stop_light); 
  printf("address of function inc() is :%p\n", &inc);
  while (i < 36) {
    stop_light();
    i = inc(i);
  }
}
