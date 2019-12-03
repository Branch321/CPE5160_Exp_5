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
	STATE_7
} states_t;

typedef enum {
	RELEASED,
	R_EDGE,
	PRESSED,
	F_EDGE
} b_states_t;

//void blinking_lights_isr(void);

void set_lights(bit green, bit amber, bit yellow, bit red);


void Button_State_Change(b_states_t button_state);

#endif