#ifndef _BLINKING_LIGHTS_H
#define _BLINKING_LIGHTS_H

#include "main.h"
#include "PORT.h"

typedef enum {
	IDLE_STATE,
	STATE_1_L_to_R,
	STATE_2_L_to_R,
	STATE_3_L_to_R,
	STATE_4_L_to_R,
	STATE_1_R_to_L,
	STATE_2_R_to_L,
	STATE_3_R_to_L,
	STATE_4_R_to_L,
	TIMER_INCREMENT_MODE
} states_t;


typedef enum {
	RELEASED,
	R_EDGE,
	PRESSED,
	F_EDGE
} b_states_t;

/*
 *
 */
void set_lights(uint8_t light_config);

#endif
