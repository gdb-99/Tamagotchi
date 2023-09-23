/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../GUI.h"
#include "../audio.h"
#include "../RIT/RIT.h"
#include "../adc/adc.h"


int happiness = 3;
int satiety = 3;

int old_satiety = 3;
int old_happiness = 3;

int age = 0;
int reset = 0;


static int joystick_select = 0;
static int joystick_left = 0;
static int joystick_right = 0;

int n_volume_lines;
float current_volume;

static int count = 0;

//healing song
int MealSongNotes[5] = {e4, e4, e4, c4, g4};
int MealSongDurations[5] = {e4_h, e4_h, e4_h / 2, c4_h / 2, g4_h};

//healing song
int SnackSongNotes[5] = {e4, e4, e4, c4, g4};
int SnackSongDurations[5] = {e4_h , e4_h, e4_h/ 2, c4_h / 2, g4_h};

//low hp
int DeathSongNotes[6] = {a3b, d3, a3b, d3, a3b, d3};
int DeathSongDurations[6] = {a3b_h, d3_h, a3b_h, d3_h, a3b_h, d3_h};

//level up
int CuddleSongNotes[4] = {d4, d4, d4, a4};
int CuddleSongDurations[4] = {d4_h, d4_h / 2, d4_h / 2, a4_h};

int mealSongIndex = 0;
int playingMealSong = 0;

int snackSongIndex = 0;
int playingSnackSong = 0;


int deathSongIndex = 0;
int playingDeathSong = 0;

int playingCuddleSong = 0;
int cuddleSongIndex = 0;

int pauseCycles = 0;

void decrease_stats(){
	old_satiety = satiety;
	satiety--;
		
	old_happiness = happiness;
	happiness--;
		
	draw_candies(old_satiety, satiety);
	draw_balls(old_happiness, happiness);
	
	if (satiety == 0 || happiness == 0) {
		disable_timer(0);
		reset = 1;
		
		playingDeathSong = 1;
		playingCuddleSong = 0;
		playingSnackSong = 0;
		playingMealSong = 0;
		
		draw_reset();
		draw_ko_cyn();
		
		return;
	}
}

void meal(){
	if(satiety == 3) return;
	
	old_satiety = satiety;
	satiety++;
	
	playingMealSong = 1;
}

void snack(){
	if(happiness == 3) return;
	
	old_happiness = happiness;
	happiness++;
	
	playingSnackSong = 1;
}

void cuddle() {
	if(happiness == 3) return;
	
	old_happiness = happiness;
	happiness++;
	
	playingCuddleSong = 1;
}

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	age++;
	draw_age(age);
	draw_normal_cyn(age);
	
	if(age % 5 == 0) {
  		decrease_stats();
	}

  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  
	/****************************************************************************
	** Audio Management
	*****************************************************************************/
		
	ADC_start_conversion();

	// DRAW VOLUME
	current_volume = getVolume();
	if (current_volume < 0.01) {
		n_volume_lines = 0;
	} else if (current_volume < 0.333) {
		n_volume_lines = 1;
	} else if (current_volume < 0.666) {
		n_volume_lines = 2;
	} else {
		n_volume_lines = 3;
	}
	draw_volume_lines(n_volume_lines);

	
	if (!reset && !isPlaying() && playingMealSong) {
		playNote(MealSongNotes[mealSongIndex], MealSongDurations[mealSongIndex]);
		mealSongIndex++;
		
		if (mealSongIndex == 5) {
			mealSongIndex = 0;
			playingMealSong = 0;
			
			draw_meal_animation();
			draw_candies(old_satiety, satiety);
		}
	}
	
	if (!reset && !isPlaying() && playingSnackSong) {
		playNote(SnackSongNotes[snackSongIndex], SnackSongDurations[snackSongIndex]);
		snackSongIndex++;
		if (snackSongIndex == 5) {
			snackSongIndex = 0;
			playingSnackSong = 0;
			
			draw_snack_animation();
			draw_balls(old_happiness, happiness);
		}
	}
		
	// death song
	if (reset && !isPlaying() && playingDeathSong) {
		playNote(DeathSongNotes[deathSongIndex], DeathSongDurations[deathSongIndex]);
		deathSongIndex++;
		
		if (deathSongIndex == 6) {
			deathSongIndex = 0;
			playingDeathSong = 0;
			
		}
	}
	
	// cuddle song
	if (!reset && !isPlaying() && playingCuddleSong) {
		playNote(CuddleSongNotes[cuddleSongIndex], CuddleSongDurations[cuddleSongIndex]);
		cuddleSongIndex++;
		if (cuddleSongIndex == 4) {
			cuddleSongIndex = 0;
			playingCuddleSong = 0;
			
			draw_cuddle_animation();
			draw_balls(old_happiness, happiness);
		}
	}
	
	
	if(!isPlaying() && !playingCuddleSong && !playingMealSong && !playingDeathSong ) {
		
		/****************************************************************************
	** Touchscreen Management
	*****************************************************************************/
	
		if(!reset) {
			if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
				if(display.y < 196 && display.y > 113 && display.x > 60 && display.x < 170){
					cuddle();
				}
			}
		}
		
			/****************************************************************************
	**	JOYSTICK Management
	*****************************************************************************/
		
		if ( (LPC_GPIO1->FIOPIN & (1<<25)) == 0 ) {
			// Joystick SELECT pressed
			joystick_select++;
			
			if(!reset) {
				// SELECT after having chosen snack option
				if (joystick_left > 0) {
					snack();
					
					// Disable left after animation and stats animation
					draw_snack_option(0);
					joystick_left = 0;
				}
				// SELECT after having chosen meal option
				else if (joystick_right > 0) { 
					meal();
					
					// Disable right after animation and stats animation
					draw_meal_option(0);
					joystick_right = 0;
				}
			}
			else {
				age = 0;
				reset = 0;
				
				happiness = 3;
				satiety = 3;
				old_satiety = 3;
				old_happiness = 3;
				
				// Redraw default screen
				// and start counting age again
				draw_default_screen();
				enable_timer(0);
			}
			
		} else joystick_select = 0;
		
		if (!reset) {
			if ( (LPC_GPIO1->FIOPIN & (1<<27)) == 0 ) {
				// Joystick LEFT pressed
					joystick_left++;
				
				// If I previously pressed the right option
				// I need to disable it
				if (joystick_right != 0) {
					joystick_right = 0;
					
					playNote(CLICK_NOTE, CLICK_DURATION);
					draw_meal_option(0);
				}
				
				draw_snack_option(1);
			}
			
			if ( (LPC_GPIO1->FIOPIN & (1<<28)) == 0 ) {
				// Joystick RIGHT pressed
				joystick_right++;
				
				// If I previously pressed the left option
				// I need to disable it
				if (joystick_left != 0) {
					joystick_left = 0;
					
					playNote(CLICK_NOTE, CLICK_DURATION);
					draw_snack_option(0);
				}
				
				draw_meal_option(1);
			}
		}
	}
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
