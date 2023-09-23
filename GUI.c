#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"

#include "my_drawings.h"

#include <stdio.h>  

#define PADDING 32
#define CANDY_PADDING PADDING/2 + 3*PADDING


void draw_balls(int old_happiness, int happiness){
	if (old_happiness == 3 && happiness == 3) {
		int i;
		for (i = 1; i <= 3; i++) 
			make_drawing(&ball_full, (i-0.5)*PADDING, 56, 0);
	}
	
	//stats decreased: there must be a number of empty pokéballs that equals the difference between old_happiness and happiness
	if (old_happiness > happiness) {
		make_drawing(&ball_empty, (old_happiness-0.5)*PADDING, 56, 0);
		} //stats increased: the same as before, but reversed
	else if (old_happiness < happiness) {
		make_drawing(&ball_full, (happiness-0.5)*PADDING, 56, 0);
	}
}

//same logic as happiness stats
void draw_candies(int old_satiety, int satiety){
	if (old_satiety == 3 && satiety == 3) {
		int i;
		for (i = 1; i <= 3; i++) 
			make_drawing(&candy_full, CANDY_PADDING + (i-0.5)*PADDING, 56, 0);
	}
	
	if (old_satiety > satiety) {
		make_drawing(&candy_empty, CANDY_PADDING + (old_satiety-0.5)*PADDING, 56, 0);
	}
	else if (old_satiety < satiety) {
		make_drawing(&candy_full, CANDY_PADDING + (satiety-0.5)*PADDING, 56, 0);
	}
}

void draw_normal_cyn(int age){
	int animation = age % 3;
	switch (animation) {
		case 0: make_drawing(&normal_1, 75, 130, 0);
		break;
		case 1: make_drawing(&normal_2, 75, 130, 0);
		break;
		case 2: make_drawing(&normal_3, 75, 130, 0);
		break;
	}
}

void draw_ko_cyn(void){
	color_area(90, 71, 75, 130, White);
	make_drawing(&ko_1, 75, 130, 1);
	make_drawing(&ko_2, 75, 130, 1);
	make_drawing(&ko_1, 75, 130, 1);
	make_drawing(&ko_2, 75, 130, 1);
	make_drawing(&ko_1, 75, 130, 1);
	make_drawing(&ko_2, 75, 130, 1);
	make_drawing(&ko_1, 75, 130, 1);
	make_drawing(&ko_2, 75, 130, 1);
	make_drawing(&ko_3, 75, 130, 1);
}

void draw_meal_animation(void){
	color_area(90, 71, 75, 130, White);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	make_drawing(&meal_1, 120, 130, 1);
	make_drawing(&meal_2, 120, 130, 1);
	color_area(90, 71, 120, 130, White);
	make_drawing(&normal_3, 75, 130, 1);
}

void draw_snack_animation(void){
	color_area(90, 71, 75, 130, White);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);	
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	make_drawing(&snack_1, 30, 130, 1);
	make_drawing(&snack_2, 30, 130, 1);
	color_area(90, 71, 30, 130, White);
	make_drawing(&normal_3, 75, 130, 1);
}

void draw_cuddle_animation(void) {
	color_area(90, 71, 75, 130, White);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	make_drawing(&cuddle_1, 75, 130, 1);
	make_drawing(&cuddle_2, 75, 130, 1);
	color_area(90, 71, 75, 130, White);
	make_drawing(&normal_3, 75, 130, 1);
}


void draw_age(int age) {
	char buffer[20];
	int h, m, s;
	
	h = (age/3600); 
	m = (age -(3600*h))/60;
	s = (age -(3600*h)-(m*60));
	snprintf(buffer, sizeof(buffer), "Age: %02d:%02d:%02d", h, m, s);
	
	GUI_Text(68, 8, (uint8_t *) buffer, Black, White);
}

void draw_snack_option(int highlighted) {
	if (highlighted) {
		color_area(240/2, 320 - 32 - 16, 0, 320 - 32 - 16 + 1, Red);
		GUI_Text(PADDING/2 + 28, 320 - 32, (uint8_t *) "SNACK", White, Red);
	}	
	else {
		color_area(240/2, 320 - 32 - 16, 0, 320 - 32 - 16 + 1, White);
		GUI_Text(PADDING/2 + 28, 320 - 32, (uint8_t *) "SNACK", Black, White);
		LCD_DrawLine(120, 320 - 32 - 16, 120, 320, Black);
	}
}

void draw_meal_option(int highlighted) {
	if (highlighted) {
		color_area(240/2 - 1, 320 - 32 - 16, 240/2 + 1, 320 - 32 - 16 + 1, Blue);
		GUI_Text(CANDY_PADDING + PADDING/2 + 32, 320 - 32, (uint8_t *) "MEAL", White, Blue);
	}
	else {
		color_area(240/2 - 1, 320 - 32 - 16, 240/2 + 1, 320 - 32 - 16 + 1, White);
		GUI_Text(CANDY_PADDING + PADDING/2 + 32, 320 - 32, (uint8_t *) "MEAL", Black, White);
		LCD_DrawLine(120, 320 - 32 - 16, 120, 320, Black);
	}
}

void draw_volume_lines(int n_volume_lines) {
	switch (n_volume_lines) {
		case 0: make_drawing(&volume_0, 5, 5, 0);
		break;
		case 1: make_drawing(&volume_033, 5, 5, 0);
		break;
		case 2: make_drawing(&volume_066, 5, 5, 0);
		break;
		case 3: make_drawing(&volume_100, 5, 5, 0);
		break;
	}
}

void draw_reset(void) {	
	color_area(240, 320 - 32 - 16, 0, 320 - 32 - 16 + 1, Black);
	GUI_Text(100, 320 - 32, (uint8_t *) "RESET", White, Black);
}

void draw_default_screen(void) {
	GUI_Text(PADDING/2 + 12, 32, (uint8_t *) "HAPPINESS", Red, White);
	GUI_Text(PADDING/2 + 12 + 9*8 + 12 + PADDING/2 + 24, 32, (uint8_t *) "SATIETY", Blue, White);
	
	draw_candies(3,3);
	draw_balls(3,3);
		
	LCD_DrawLine(0, 320 - 32 - 16, 240, 320 - 32 - 16, Black);
	draw_snack_option(0);
	draw_meal_option(0);
}
