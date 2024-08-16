# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_GUI_SRCS 变量
aux_source_directory(. DIR_GUI_SRCS)

include_directories(../Config)

# 生成链接库
add_library(GUI ${DIR_GUI_SRCS})
target_link_libraries(GUI PUBLIC Config)
target_sources(GUI PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/GUI_Paint.c
)
target_include_directories(GUI PUBLIC 
   ${CMAKE_CURRENT_LIST_DIR}
)
