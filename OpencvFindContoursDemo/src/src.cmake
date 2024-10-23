set(src_DIR ${CMAKE_CURRENT_LIST_DIR})
set(src_INCLUDE_DIRS ${src_DIR}/)

include_directories(${src_INCLUDE_DIRS})

include(${src_INCLUDE_DIRS}/FindContoursDemo/FindContoursDemo.cmake)

# 主模块
set(src_SOURCE
    ${src_DIR}/main.cpp
    ${FindContoursDemo_SOURCE}
)
