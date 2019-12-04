#include "Blinking_Lights.h"
#include "Buttons.h"
#include "Port.h"
#include <stdio.h>

volatile states_t SYSTEM_STATE = IDLE_STATE;
volatile uint32_t TIMER_INTERVAL_DELAY = 60;
volatile uint32_t TIMER = 0;
volatile uint8_t TIMER_NUMBER = 1;

void set_lights(uint8_t light_config) {
	light_config = light_config << 4;
	P2 = light_config|0x0F;
}

SW_values_t * SW1_p, *SW2_p, *SW3_p, *SW4_p;

void blinking_lights_isr(void) interrupt TIMER_2_OVERFLOW {
	TF2=0;
	SW1_p = Return_SW1_address();
	SW2_p = Return_SW2_address();
	SW3_p = Return_SW3_address();
	SW4_p = Return_SW4_address();
    TIMER++;

	Read_Switch(SW1_p);
	Read_Switch(SW2_p);
	Read_Switch(SW3_p);
	Read_Switch(SW4_p);
	
	if(SYSTEM_STATE == IDLE_STATE)
	{
		set_lights(15);
		if(SW1_p->SW_state==pressed)
		{
			SYSTEM_STATE = STATE_1_L_to_R;
			TIMER = 0;
			SW1_p->SW_state=held;

		}
		else if(SW4_p->SW_state==pressed)
		{
			SYSTEM_STATE = STATE_1_R_to_L;
            TIMER = 0;
			SW4_p->SW_state=held;
        }
		else if(SW2_p->SW_state==pressed)
		{
			SYSTEM_STATE = TIMER_INCREMENT_MODE;
			TIMER = 0;
			SW2_p->SW_state=held;

		}
		else if(SW3_p->SW_state == pressed)
		{
			SYSTEM_STATE = TIMER_INCREMENT_MODE;
			SW3_p->SW_state=held;
			TIMER = 0;
		}
	}
	else if(SYSTEM_STATE == STATE_1_L_to_R)
	{
		set_lights(7);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_2_L_to_R;
			TIMER=0;
		}
		else if(SW1_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW1_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_2_L_to_R)
	{
		set_lights(3);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_3_L_to_R;
			TIMER=0;
		}
		else if(SW1_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW1_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_3_L_to_R)
	{
		set_lights(1);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_4_L_to_R;
			TIMER=0;
		}
		else if(SW1_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW1_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_4_L_to_R)
	{
		set_lights(0);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_1_L_to_R;
			TIMER=0;
		}
		else if(SW1_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW1_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_1_R_to_L)
	{
		set_lights(14);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_2_R_to_L;
			TIMER=0;
		}
		else if(SW4_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW4_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_2_R_to_L)
	{
		set_lights(12);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_3_R_to_L;
			TIMER=0;
		}
		else if(SW4_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE; 
			SW4_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_3_R_to_L)
	{
		set_lights(8);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_4_R_to_L;
			TIMER=0;
		}
		else if(SW4_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
 		    SW4_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE == STATE_4_R_to_L)
	{
		set_lights(0);
		if(TIMER>=TIMER_INTERVAL_DELAY)
		{
			SYSTEM_STATE = STATE_1_R_to_L;
			TIMER=0;
		}
		else if(SW4_p->SW_state == pressed)
		{
			SYSTEM_STATE = IDLE_STATE; 
			SW4_p->SW_state = held;
		}
	}
	else if(SYSTEM_STATE==TIMER_INCREMENT_MODE)
	{
	    set_lights(~TIMER_NUMBER);
		TIMER_INTERVAL_DELAY = TIMER_NUMBER*60;
	    if(SW2_p->SW_state==pressed)
		{
			TIMER_NUMBER++;
			if(TIMER_NUMBER>=15)
			{
				TIMER_NUMBER=15;
			}
			SW2_p->SW_state = held;
		}
		else if(SW3_p->SW_state==pressed)
		{
			TIMER_NUMBER--;
			if(TIMER_NUMBER<=1)
			{
				TIMER_NUMBER=1;
			}
			SW3_p->SW_state = held;
		}
		else if(SW1_p->SW_state==pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW1_p->SW_state = held;
		}
		else if(SW4_p->SW_state==pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
			SW4_p->SW_state = held;
		}
	}
}


