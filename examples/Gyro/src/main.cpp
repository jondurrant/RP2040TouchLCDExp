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
#include "QMI8658.h"
}

#include <math.h>
#include "IMUfilter.h"


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


   QMI8658_init();
   float acc[3];
   float gyro[3];
   unsigned int tim_count;
   float temp;
   IMUfilter imuFilter(0.01, 0.1);

    for (;;){
    	 //sleep_ms(500);

    	 for (int i=0; i < 100; i++){
    		 QMI8658_read_xyz( acc,  gyro,  &tim_count);
    		 imuFilter.updateFilter(
    				 gyro[0],
					 gyro[1],
					 gyro[2],
					 acc[0],
					 acc[1],
					 acc[2]
					 );
    		 sleep_ms(10);
    	 }
    	 temp =  QMI8658_readTemp();

    	 /*
    	 printf("ACC %.2f, %.2f, %.2f  GYRO %.2f, %.2f, %.2f Time %d, %0.2fC \n",
    	    			 acc[0], acc[1], acc[2],
    					 gyro[0], gyro[1], gyro[2],
    					 tim_count,
    					 temp
    	    			 );
    	    			 */

    	 imuFilter.computeEuler();
    	 printf("RPY %.2f, %.2f, %.2f\n",
    			 imuFilter.getRoll(),
				 imuFilter.getPitch(),
				 imuFilter.getYaw()
    			 );

    	 /*
    	 printf("ACC %.2f, %.2f, %.2f  GYRO %.2f, %.2f, %.2f Time %d, %0.2fC \n",
    			 acc[0], acc[1], acc[2],
				 gyro[0], gyro[1], gyro[2],
				 tim_count,
				 temp
    			 );

    	 double apitch =  atan (acc[0]/sqrt(acc[1]*acc[1] + acc[2]*acc[2])) ;
    	 double aroll = atan (acc[1]/sqrt(acc[0]*acc[0] + acc[2]*acc[2]));
    	 double ayaw = atan (sqrt(acc[0]*acc[0] + acc[2]*acc[2])/acc[2]);
    	 printf("APRY %.2f, %.2f, %.2f\n", apitch, aroll, ayaw);
    	 double gpitch =  atan (gyro[0]/sqrt(gyro[1]*gyro[1] + gyro[2]*gyro[2])) ;
    	 double groll = atan (gyro[1]/sqrt(gyro[0]*gyro[0] + gyro[2]*gyro[2]));
    	 double gyaw = atan (sqrt(gyro[0]*gyro[0] + gyro[2]*gyro[2])/gyro[2]);
    	 printf("GPRY %.2f, %.2f, %.2f\n", gpitch, groll, gyaw);
    	 */

    }

}
