add_executable(${NAME}
        imageData.c
        LCD_1in28_LVGL_test.c
        LVGL_example.c
        main.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	pico_stdlib
	Config 
	LCD 
	Touch 
#	GUI
#	Fonts
	QMI8658 
	lvgl
	hardware_clocks 
	hardware_rtc 
	hardware_adc
	hardware_dma
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 0)

