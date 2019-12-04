#ifndef _BLINKING_LIGHTS_H
#define _BLINKING_LIGHTS_H

#include "main.h"
#include "PORT.h"

// possible system states
typedef enum {
	IDLE_STATE,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_5,
	STATE_6,
	STATE_7,
	TIMER_INCREMENT_MODE
} states_t;


typedef enum {
	RELEASED,
	R_EDGE,
	PRESSED,
	F_EDGE
} b_states_t;

void LED_State_Change();

void set_lights(uint8_t light_config);

#endif