#include "Blinking_Lights.h"

volatile bit Button_1 = 0;
volatile states_t SYSTEM_STATE = IDLE_STATE;
volatile uint32_t TIMER = 0;
volatile bit Button_4 = 0;
volatile uint32_t TIMER_INTERVAL=1000;
sbit SW1 = P2^0;

void set_lights(bit green, bit amber, bit yellow, bit red) {
    GREENLED = green;
    AMBERLED = amber;
    YELLOWLED = yellow;
    REDLED = red;
}


void blinking_lights_isr(void) interrupt TIMER_2_OVERFLOW {
    TF2 = 0; // clear interrupt flag
    TIMER++; // increment timer
	SW1 = 1;
	/*
	if(SW1==0)
	{
		Button_1 = 1;
	}
	*/
	Button_1 = 1;
	switch(SYSTEM_STATE)
	{
		case IDLE_STATE:
			set_lights(1,1,1,1);
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_1;
				set_lights(0,1,1,1);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_7;
				set_lights(1,1,1,0);
				TIMER = 0;
			}
			break;
		case STATE_1:
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_2;
				set_lights(0,0,1,1);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = IDLE_STATE;
				TIMER = 0;
			}
			break;
		case STATE_2:
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_3;
				set_lights(0,0,0,1);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_1;
				set_lights(0,1,1,1);
				TIMER = 0;
			}
			break;
		case STATE_3:
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_4;
				set_lights(0,0,0,0);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_2;
				set_lights(0,0,1,1);
				TIMER = 0;
			}
			break;
		case STATE_4:
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_5;
				set_lights(1,0,0,0);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_3;
				set_lights(0,0,0,1);
				TIMER = 0;
			}
			break;
		case STATE_5:
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_6;
				set_lights(1,1,0,0);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
			 	SYSTEM_STATE = STATE_4;
				set_lights(0,0,0,0);
				TIMER = 0;
			}
			break;
		case STATE_6:		
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_7;
				set_lights(1,1,1,0);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_5;
				set_lights(1,0,0,0);
				TIMER = 0;
			}
			break;
		case STATE_7:	
			if(Button_1==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = IDLE_STATE;
				set_lights(1,1,1,1);
				TIMER = 0;
			}
			else if(Button_4==1&&TIMER==TIMER_INTERVAL)
			{
				SYSTEM_STATE = STATE_6;
				set_lights(1,1,0,0);
				TIMER = 0;
			}
			break;
	}
}
