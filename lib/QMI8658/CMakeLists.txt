# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_ePaper_SRCS 变量
aux_source_directory(. DIR_QMI8658_SRCS)

include_directories(../Config)

# 生成链接库
add_library(QMI8658 ${DIR_QMI8658_SRCS})
target_sources(QMI8658 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/QMI8658.c
)

target_include_directories(QMI8658 PUBLIC 
   ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(QMI8658 PUBLIC Config)