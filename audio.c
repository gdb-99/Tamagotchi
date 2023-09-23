#include "RIT/RIT.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void playNote(int frequency, unsigned int duration) {
	// play a note using RIT with period = frequency
	if (frequency == 0) {
		setSilent(1);
	}
	setPeriods(duration); // 1/4 of a second
	init_RIT(frequency);									/* RIT Initialization 50 msec       	*/
	enable_RIT();
}