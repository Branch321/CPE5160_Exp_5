#ifndef _BUTTONS_H
#define _BUTTONS_H

#include "main.h"

#define interval 1
//#define Input_Port P2
#define debounce_timer 100

typedef enum{
	not_pressed,
	debounce_p,
	pressed,
	held,
	debounce_r
} switch_state_t;


typedef struct{
	uint8_t SW_mask;
	uint8_t debounce_time;
	switch_state_t SW_state;
} SW_values_t;

void Switch_Init(void);
void Read_Switch(SW_values_t * SW_input_p);
SW_values_t * Return_SW1_address();
SW_values_t * Return_SW2_address();
SW_values_t * Return_SW3_address();
SW_values_t * Return_SW4_address();

#endif
