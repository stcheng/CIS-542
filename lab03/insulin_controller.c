
enum states {off, low, high, panic};
enum actions {no_change, small_increase, large_increase, decrease};

/*
 * This is the controller.
 */
void update_state(enum actions action, enum states *state) {
	switch(*state) {
		case off:
			switch (action) {
				case no_change:
					break;
				case small_increase:
					*state = low;
					break;
				case large_increase:
					*state = low;
					break;
				case decrease:
					break;
			}
			break;
		case low:
			switch (action) {
				case no_change:
					break;
				case small_increase:
					*state = high;
					break;
				case large_increase:
					*state = panic;
					break;
				case decrease:
					*state = off;
					break;					
			}
			break;
		case high:
			switch (action) {
				case no_change:
					break;
				case small_increase:
					break;
				case large_increase:
					*state = panic;
					break;
				case decrease:
					*state = low;
					break;					
			}
			break;
		case panic:
			switch (action) {
				case no_change:
					*state = high;
					break;
				case small_increase:
					break;
				case large_increase:
					break;
				case decrease:
					*state = low;
					break;					
			}
			break;
	}  
}

/*
 * This determines how much insulin to deliver in this state, given
 * the current amount being given and the blood glucose level
 */
int calculate_insulin(int bg, int insulin, enum states state) {
   
  /*
    TODO: implement the calculation of insulin
    should always return a value between 0 and 12
  */
  
  return 0;
}