#include <stdio.h>
#include <stdlib.h>

#define failure(s) if(state != s) {printf("Test failed.\n");exit(0);}

enum states {off, low, high, panic};
enum actions {no_change, small_increase, large_increase, decrease};

int calculate_insulin(int, int, enum states);
void update_state(enum actions, enum states *);

void check(char *msg, int expected, int actual) {
  if (actual != expected) {
    printf("Test failed! expected %d but received %d: %s\n", expected, actual, msg);
    exit(0);
  } else {
    printf("Test succeed.\n");
  }
}

int main() {

  // local variables for use in testing
  enum states state;
  int bg;
  int insulin;
  enum actions action;


  /* TEST #1: transition from off to low */
  state = off;
  action = decrease;
  update_state(action, &state);
  failure(off);
  state = off;
  action = small_increase;
  update_state(action, &state);
  failure(low);
  state = off;
  action = large_increase;
  update_state(action, &state);
  failure(low);


  state = low;
  action = decrease;
  update_state(action, &state);
  failure(off);
  state = low;
  action = small_increase;
  update_state(action, &state);
  failure(high);
  state = low;
  action = large_increase;
  update_state(action, &state);
  failure(panic);
  state = low;
  action = no_change;
  update_state(action, &state);
  failure(low);

  state = high;
  action = no_change;
  update_state(action, &state);
  failure(high);
  state = high;
  action = decrease;
  update_state(action, &state);
  failure(low);
  state = high;
  action = large_increase;
  update_state(action, &state);
  failure(panic);

  state = panic;
  action = no_change;
  update_state(action, &state);
  failure(high);
  state = panic;
  action = decrease;
  update_state(action, &state);
  failure(low);
  state = panic;
  action = small_increase;
  update_state(action, &state);
  failure(panic);

  state = off;
  bg = 20;
  insulin = 5;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = off", 0, insulin);
  state = low;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = low", 0, insulin);
  bg = 51;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = low", 0, insulin);
  bg = 71;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = low", 0, insulin);
  bg = 91;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = low", 1, insulin);
  bg = 121;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = low", 3, insulin);

  state = high;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = high", 6, insulin);
  bg = 91;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = high", 8, insulin);
  bg = 71;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = high", 6, insulin);
  bg = 51;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = high", 3, insulin);
  bg = 20;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = high", 0, insulin);

  state = panic;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = panic", 0, insulin);
  bg = 51;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = panic", 0, insulin);
  bg = 71;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = panic", 0, insulin);
  bg = 91;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = panic", 3, insulin);
  bg = 121;
  insulin = calculate_insulin(bg, insulin, state);
  check("state = panic", 8, insulin);



    return 0;

}