# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_Fonts_SRCS 变量
aux_source_directory(. DIR_Fonts_SRCS)

# 生成链接库
add_library(Fonts ${DIR_Fonts_SRCS})
target_sources(Fonts PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Font12.c
    ${CMAKE_CURRENT_LIST_DIR}/Font16.c
    ${CMAKE_CURRENT_LIST_DIR}/Font20.c
    ${CMAKE_CURRENT_LIST_DIR}/Font24.c
    ${CMAKE_CURRENT_LIST_DIR}/Font8.c
)
target_include_directories(Fonts PUBLIC 
   ${CMAKE_CURRENT_LIST_DIR}
)
