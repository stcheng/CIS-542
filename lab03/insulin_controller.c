
enum states {off, low, high, panic};
enum actions {no_change, small_increase, large_increase, decrease};

/*
 * This is the controller.
 */
void update_state(enum actions action, enum states *state) {
	switch(*state) {
		case off:
			switch (action) {
				case small_increase:
					*state = low;
					break;
				case large_increase:
					*state = low;
					break;
				default:
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
				case large_increase:
					*state = panic;
					break;
				case decrease:
					*state = low;
					break;	
				default:
					break;				
			}
			break;
		case panic:
			switch (action) {
				case no_change:
					*state = high;
					break;
				case decrease:
					*state = low;
					break;
				default:
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

    switch (state) {
    	case low:
    		if (bg >= 20 && bg <= 50) {
    			return 0;
    		} else if (bg >= 51 && bg <= 70) {
    			return (insulin-2<0)?0:insulin-2;
    		} else if (bg >= 71 && bg <= 90) {
    			return (insulin-1<0)?0:insulin-1;
    		} else if (bg >= 91 && bg <= 120) {
    			return (insulin+1>12)?12:insulin+1;
    		} else if (bg > 120) {
    			return (insulin+2>12)?12:insulin+2;
    		}
    	case high:
    		if (bg >= 20 && bg <= 50) {
    			return 0;
    		} else if (bg >= 51 && bg <= 70) {
    			return (insulin-3<0)?0:insulin-3;
    		} else if (bg >= 71 && bg <= 90) {
    			return (insulin-2<0)?0:insulin-2;
    		} else if (bg >= 91 && bg <= 120) {
    			return (insulin+2>12)?12:insulin+2;
    		} else if (bg > 120) {
    			return (insulin+3>12)?12:insulin+3;
    		}
    	case panic:
    		if (bg >= 20 && bg <= 50) {
    			return 0;
    		} else if (bg >= 51 && bg <= 70) {
    			return (insulin-4<0)?0:insulin-4;
    		} else if (bg >= 71 && bg <= 90) {
    			return (insulin-3<0)?0:insulin-3;
    		} else if (bg >= 91 && bg <= 120) {
    			return (insulin+3>12)?12:insulin+3;
    		} else if (bg > 120) {
    			return (insulin+5>12)?12:insulin+5;
    		}
    	default:
    		break;
    }
    return 0;
}