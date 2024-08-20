cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME Hack) # <-- Name your project/executable here!
set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../../lib")
#set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")

message(LIB_DIR="${LIB_DIR}")

include(${LIB_DIR}/Config/CMakeLists.txt)
include(${LIB_DIR}/LCD_LVGL/CMakeLists.txt)
include(${LIB_DIR}/QMI8658/CMakeLists.txt)
include(${LIB_DIR}/Touch/CMakeLists.txt)

set(LV_CONF_DIR "${CMAKE_CURRENT_LIST_DIR}/port/lvgl/")
set(LVGL_DIR "${LIB_DIR}/lvgl/")
include(lvgl.cmake)

add_subdirectory(src)

#Set up files for the release packages
install(CODE "execute_process(COMMAND $ENV{HOME}/bin/picoDeploy.sh ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}.elf)")

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}.uf2
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
