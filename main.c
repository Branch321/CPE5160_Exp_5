/* Names: Tyler Andrews, Brennan Campbell, Tyler Tetens
 * Project: Experiment 5
 * Class: Cpe5160
 * Professor: Mr. Younger
*/

#include "main.h"
#include "PORT.h"
#include "sEOS.h"
#include "Buttons.h"
//#include "Blinking_Lights.h"

void main(void) {
    sEOS_init(1); // initialize sEOS interrupt at 1ms
	Switch_Init();
    while(1) {
        go_to_sleep(); // enter idle mode
    }
}