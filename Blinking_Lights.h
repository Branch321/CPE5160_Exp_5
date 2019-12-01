#ifndef _BLINKING_LIGHTS_H
#define _BLINKING_LIGHTS_H

#include "main.h"

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


states_t SYSTEM_STATE = IDLE_STATE;
uint32_t TIMER = 0;
bit Button_1 = 0;
bit Button_4 = 0;

void blinking_lights_isr(void);

#endif