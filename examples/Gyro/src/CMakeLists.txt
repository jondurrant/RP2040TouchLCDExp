add_executable(${NAME}
        main.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	pico_stdlib
	Config 
	LCD 
	Touch 
	GUI
	Fonts
	QMI8658 
	hardware_clocks 
	hardware_rtc 
	hardware_adc
	openimufilter
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

