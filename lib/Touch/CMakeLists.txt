aux_source_directory(. DIR_Touch_SRCS)

include_directories(../Config)

add_library(Touch ${DIR_Touch_SRCS})
target_sources(Touch PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CST816S.c
)

target_include_directories(Touch PUBLIC 
   ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(Touch PUBLIC Config)