/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "adc/adc.h"

#include "GUI.h"
#include "my_drawings.h"
#include "RIT/RIT.h"

#define SIMULATOR 0

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	ADC_init();
  LCD_Initialization();

	TP_Init();
	TouchPanel_Calibrate();
	LCD_Clear(White);

	draw_default_screen();
	
	// Timer0 handles animations and stats
	// Timer1 handles the joystick actions
	if (!SIMULATOR) {
//		init_RIT(0x1312D0);
//		/* K_RIT = 50ms * 100Mhz = 
//			= 50 * 10^-3 s * 25 * 10^6 Hz =
//			= 0x1312D0
//		*/
//		enable_RIT();
		
		joystick_init();
		init_timer(0, 0x017D7840);
		/* K_0 = 1s * 25 Mhz =
			= 1 s * 25 * 10^6 Hz =
			= 25000000 = 0x017D7840
		*/
		enable_timer(0);
		
		init_timer(1, 0x1312D0);
		enable_timer(1);
	}
	else {
		init_RIT(0x000000A0);
		enable_RIT();
		
		joystick_init();
		init_timer(0, 0x00005000);
		enable_timer(0);
	}
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
  while (1)	
  {
 		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
