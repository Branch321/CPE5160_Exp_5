#include "Blinking_Lights.h"
#include "Buttons.h"
#include "Port.h"
#include <stdio.h>

volatile states_t SYSTEM_STATE = IDLE_STATE;
volatile uint32_t TIMER_INTERVAL_DELAY = 660;
uint32_t TIMER = 0;

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
    TIMER++; // increment timer

	Read_Switch(SW1_p);
	Read_Switch(SW2_p);
	Read_Switch(SW3_p);
	Read_Switch(SW4_p);
	
	if(TIMER==TIMER_INTERVAL_DELAY)
	{
		LED_State_Change();
		TIMER=0;
	}
}

void LED_State_Change(void)
{
	if(SYSTEM_STATE == IDLE_STATE)
	{
		set_lights(15);
		if(SW2_p->SW_state==pressed||SW3_p->SW_state==pressed)
		{
			SYSTEM_STATE=TIMER_INCREMENT_MODE;
		}
		
		else if(SW1_p->SW_state==pressed)
		{
			SYSTEM_STATE = STATE_1;
			set_lights(0x7F);
			TIMER = 0;
		}	
	}
	else if(SYSTEM_STATE==STATE_1)
	{

		SYSTEM_STATE = STATE_2;
		set_lights(0x3F);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==STATE_2)
	{
		SYSTEM_STATE = STATE_3;
		set_lights(0x1F);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==STATE_3)
	{
		SYSTEM_STATE = STATE_4;
		set_lights(0x0F);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==STATE_4)
	{

		SYSTEM_STATE = STATE_5;
		set_lights(0x8F);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==STATE_5)
	{
		SYSTEM_STATE = STATE_6;
		set_lights(0xCF);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==STATE_6)
	{

		SYSTEM_STATE = STATE_7;
		set_lights(0xEF);
		TIMER = 0;

	}
	else if(SYSTEM_STATE==STATE_7)
	{
		SYSTEM_STATE = IDLE_STATE;
		set_lights(0xFF);
		TIMER = 0;
	}
	else if(SYSTEM_STATE==TIMER_INCREMENT_MODE)
	{
	    if(SW2_p->SW_state==pressed)
		{
			TIMER_INTERVAL_DELAY+=60;
			if(TIMER_INTERVAL_DELAY>=900)
			{
				TIMER_INTERVAL_DELAY=900;
			}
			set_lights(~((uint8_t) TIMER_INTERVAL_DELAY/60));
		}
		else if(SW3_p->SW_state==pressed)
		{
			TIMER_INTERVAL_DELAY-=60;
			if(TIMER_INTERVAL_DELAY<60)
			{
				TIMER_INTERVAL_DELAY=60;
			}
			set_lights(~((uint8_t) TIMER_INTERVAL_DELAY/60));
		}
		else if(SW1_p==pressed||SW4_p==pressed)
		{
			SYSTEM_STATE = IDLE_STATE;
		}
	}
}

