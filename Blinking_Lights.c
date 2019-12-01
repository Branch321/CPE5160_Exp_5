#include "Blinking_Lights.h"
#include "PORT.h"

// Function to set lights based on input numbers
void set_lights(bit green, bit amber, bit yellow, bit red) {
    GREENLED = green;
    AMBERLED = amber;
    YELLOWLED = yellow;
    REDLED = red;
}

// Function to control traffic light system state
void blinking_lights_isr(void) interrupt TIMER_2_OVERFLOW {
    TF2 = 0; // clear interrupt flag
    TIMER++; // increment timer

	// Debounce this crap
	if(SW1)
	{
		Button_1 = ~Button_1;
	}
	else if(SW4)
	{
		Button_4 = ~Button_4;
	}
	// TODO: may need to worry about set_lights functions being inside if statements
	switch(SYSTEM_STATE)
	{
		case IDLE_STATE:
			set_lights(0,0,0,0);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_1;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_7;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_1:
			set_lights(1,0,0,0);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_2;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_2:
			set_lights(1,1,0,0);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_3;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_1;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_3:
			set_lights(1,1,1,0);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_4;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_2;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_4:
			set_lights(1,1,1,1);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_5;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_3;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_5:
			set_lights(0,1,1,1);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_5;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
			 	SYSTEM_STATE = STATE_4;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_6:
			set_lights(0,0,1,1);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_7;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_5;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_7:
			set_lights(0,0,0,1);
			if(Button_1&&TIMER==1000)
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			else if(Button_4&&TIMER==1000)
			{
				SYSTEM_STATE = STATE_6;
				TIMER = 0;
			}
			else
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
	}
}
