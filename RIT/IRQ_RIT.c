/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GUI.h"
//#include "../led/led.h"

#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int n_periods = 440;
int period_counter = 0;
float volume = 1.0f;
float adjustedValue = 0.0f;
int silent = 0;
int playing = 0;

uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


void setPeriods(int value) {
	n_periods = value;
}

void setSilent(int value) {
	if (value == 1) {
		silent = 1;
	} else {
		silent = 0;
	}
}

void setVolume(float new_volume) {
	volume = new_volume;
}

float getVolume() {
		return volume;
}

int isPlaying() {
	return playing;
}


void RIT_IRQHandler (void)
{			
	// plays a note on the DAC
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	
	playing = 1;

	if (!silent) {
		currentValue = SinTable[sineticks];
		currentValue -= 410;
		currentValue /= 1;
		currentValue += 410;
		adjustedValue = ((float)(currentValue)) * volume;
		currentValue = (int)adjustedValue;
		LPC_DAC->DACR = currentValue <<6;
	}
	sineticks++;
	
	if(sineticks==45) {
		sineticks=0;
		period_counter++;
	}
	
	if(period_counter >= n_periods)
	{
		period_counter = 0;
		setSilent(0);
		playing = 0;
		disable_RIT();
	}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
