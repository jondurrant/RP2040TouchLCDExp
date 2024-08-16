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
#include "CST816S.h"
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


   CST816S_init(CST816S_Gesture_Mode);

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
	   Paint_Clear(BLACK);

	   Paint_DrawCircle(
	   			   LCD_1IN28.WIDTH /2,
	   			   LCD_1IN28.HEIGHT/2,
				   LCD_1IN28.HEIGHT/2-3,
	   			   RED,
	   			   DOT_PIXEL_3X3,
	   			   DRAW_FILL_EMPTY);

	   Paint_DrawCircle(
			   LCD_1IN28.WIDTH /2-55,
			   LCD_1IN28.HEIGHT/2,
			   50,
			   GREEN,
			   DOT_PIXEL_3X3,
			   DRAW_FILL_EMPTY);

	   Paint_DrawCircle(
	  			   LCD_1IN28.WIDTH /2+55,
	  			   LCD_1IN28.HEIGHT/2,
	  			   50,
	  			   BLUE,
	  			   DOT_PIXEL_3X3,
	  			   DRAW_FILL_EMPTY);

	   LCD_1IN28_Display( image);


   }


   uint8_t guesture;
   CST816S point ;
   uint16_t x =0;
   uint16_t y = 0;
    for (;;){
    	 sleep_ms(500);
    	 Paint_DrawCircle(
				   LCD_1IN28.WIDTH /2-55,
				   LCD_1IN28.HEIGHT/2,
				   50-6,
				   BLACK,
				   DOT_PIXEL_3X3,
				   DRAW_FILL_FULL);

		   Paint_DrawCircle(
					   LCD_1IN28.WIDTH /2+55,
					   LCD_1IN28.HEIGHT/2,
					   50-6,
					   BLACK,
					   DOT_PIXEL_3X3,
					   DRAW_FILL_FULL);

		   LCD_1IN28_Display( image);



    	 point = CST816S_Get_Point();
    	 //guesture = CST816S_Get_Gesture();
    	 printf("Point %d, %d %d\n",
    			 point.x_point,
				 point.y_point,
				 guesture);

    	 if (( point.x_point != x) || ( point.y_point != y)){
    		 x =  point.x_point;
    		 y =  point.y_point;

    		 uint16_t mx = abs(x - (LCD_1IN28.WIDTH /2-55));
    		 uint16_t my = abs(y - (LCD_1IN28.HEIGHT /2));
    		 if ((mx < 50) && (my < 50)){
    			 	 printf("Left\n");
    			 	 Paint_DrawCircle(
							   LCD_1IN28.WIDTH /2-55,
							   LCD_1IN28.HEIGHT/2,
							   50,
							   GREEN,
							   DOT_PIXEL_3X3,
							   DRAW_FILL_FULL);
    			 	LCD_1IN28_Display( image);
    		 }

    		 mx = abs(x - (LCD_1IN28.WIDTH /2+55));
			 my = abs(y - (LCD_1IN28.HEIGHT /2));
			 if ((mx < 50) && (my < 50)){
					 printf("Right\n");
					 Paint_DrawCircle(
					  			   LCD_1IN28.WIDTH /2+55,
					  			   LCD_1IN28.HEIGHT/2,
					  			   50,
					  			   BLUE,
					  			   DOT_PIXEL_3X3,
								   DRAW_FILL_FULL);
					 LCD_1IN28_Display( image);
			 }
    	 }


    	 printf("Done\n");
    }

}
