#include <stdio.h>
#include <stdlib.h>

#define failure(s) if(state != s) {printf("Test failed.\n");exit(0);}

enum states {off, low, high, panic};
enum actions {no_change, small_increase, large_increase, decrease};

void update_state(enum actions, enum states *);

int main() {

  // local variables for use in testing
  enum states state;
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




  return 0;

}