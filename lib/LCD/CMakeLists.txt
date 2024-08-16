# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_ePaper_SRCS 变量
aux_source_directory(. DIR_LCD_SRCS)

include_directories(../Config)

# 生成链接库
add_library(LCD ${DIR_LCD_SRCS})
target_link_libraries(LCD PUBLIC Config)
target_sources(LCD PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/LCD_1in28.c
)

target_include_directories(LCD PUBLIC 
   ${CMAKE_CURRENT_LIST_DIR}
)