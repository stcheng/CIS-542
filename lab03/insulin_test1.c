#include <stdio.h>
#include <stdlib.h>

enum states {off, low, high, panic};
enum actions {no_change, small_increase, large_increase, decrease};

void update_state(enum actions, enum states *);

int main() {

  // local variables for use in testing
  enum states state;
  enum actions action;


  /* TEST #1: transition from off to low */
  state = off;
  action = small_increase;
  update_state(action, &state);
  if (state != low) {
    printf("Test failed: transition from off to low\n");
    exit(0);
  }
  else {
    printf("good job.\n");
  }

  /* TEST #2: transition from low to high */
  update_state(action, &state);
  if (state != high) {
    printf("Test failed: transition from off to low\n");
    exit(0);
  }
  else {
    printf("good job again.\n");
  }
  /*
    TODO: implement the rest of the test cases
  */

    return 0;

}