/* Names: Tyler Andrews, Brennan Campbell, Tyler Tetens
 * Project: Experiment 5
 * Class: Cpe5160
 * Professor: Mr. Younger
*/

#include "main.h"
#include "PORT.h"
#include "sEOS.h"
//#include "Blinking_Lights.h"

void main(void) {
    sEOS_init(1); // initialize sEOS interrupt at 1ms
	//SW1 = 1; // Have to set to 1 to be able to read an input in 8051
	//SW2 = 1;
	//SW3 = 1;
    while(1) {
        go_to_sleep(); // enter idle mode
    }
}