#include "LCD_test.h"  //example
#include "pico/stdlib.h"
#include <stdio.h>

int main(void)
{
	stdio_init_all();
	sleep_ms(2000);
	printf("GO\n");

    LCD_1in28_LVGL_Test();

    return 0;
}
