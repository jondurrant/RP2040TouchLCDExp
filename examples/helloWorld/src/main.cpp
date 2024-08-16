/*
 * main.cpp
 *
 *  Created on: 11 Jul 2024
 *      Author: jondurrant
 */

#include "pico/stdlib.h"
#include <stdio.h>

extern "C"{

#include "LCD_1in28.h"
#include "GUI_Paint.h"
}



int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    if (DEV_Module_Init() != 0){
	   return -1;
   }
   printf("LCD_1in28_test Demo\r\n");
   LCD_1IN28_Init(HORIZONTAL);
   LCD_1IN28_Clear(BLUE);

   DEV_SET_PWM(100);

   sleep_ms(2000);

   uint32_t Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
   uint16_t *image;
   if ((image = (uint16_t *)malloc(Imagesize)) == NULL) {
	   printf("Failed to apply for black memory...\r\n");
   } else {
	   Paint_NewImage(
			   (uint8_t *)image,
			   LCD_1IN28.WIDTH,
			   LCD_1IN28.HEIGHT,
			   0,
			   GRAY);
	   Paint_SetScale(65);
	   Paint_Clear(WHITE);
	   Paint_DrawCircle(
			   LCD_1IN28.WIDTH /2,
			   LCD_1IN28.HEIGHT/2,
			   50,
			   RED,
			   DOT_PIXEL_3X3,
			   DRAW_FILL_EMPTY);
	   Paint_DrawCircle(
	   			   LCD_1IN28.WIDTH /2,
	   			   LCD_1IN28.HEIGHT/2,
				   LCD_1IN28.HEIGHT/2-3,
	   			   RED,
	   			   DOT_PIXEL_3X3,
	   			   DRAW_FILL_EMPTY);

	   Paint_DrawNum(
			   50,
			   80,
			   9.87654321,
			   &Font20,
			   3,
			   BLACK,
			   WHITE);

	   Paint_DrawString_EN(
			   LCD_1IN28.WIDTH /2-50,
			   LCD_1IN28.HEIGHT/2,
			  "DrJonEA",
			  &Font24,
			  BLUE,
			  WHITE);

	   LCD_1IN28_Display( image);


   }


    for (;;){
    	 sleep_ms(2000);
    	 printf("Done\n");
    }

}
