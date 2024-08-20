
if (NOT DEFINED LVGL_DIR)
    set(LVGL_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/lvgl")
endif()
if (NOT DEFINED LV_CONF_DIR)
    set(LV_CONF_DIR "${CMAKE_CURRENT_LIST_DIR}/port/lvgl/")
endif()


file(GLOB_RECURSE SOURCES ${LVGL_DIR}/src/*.c)
# file(GLOB_RECURSE EXAMPLE_SOURCES ${CMAKE_CURRENT_LIST_DIR}/examples/*.c)



add_library(lvgl ${SOURCES})
# add_library(LVGL_EXAMPLE STATIC ${EXAMPLE_SOURCES})

# Add include directory
target_include_directories(lvgl PUBLIC 
   ${LVGL_DIR}/src
   ${LV_CONF_DIR}
)

# Add the standard library to the build
target_link_libraries(lvgl PUBLIC 
	pico_stdlib
	)

