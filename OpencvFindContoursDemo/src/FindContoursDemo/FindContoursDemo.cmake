set(FindContoursDemo_DIR ${CMAKE_CURRENT_LIST_DIR})
set(FindContoursDemo_INCLUDE_DIRS ${FindContoursDemo_DIR}/)

include_directories(${FindContoursDemo_INCLUDE_DIRS})

# 主模块
set(FindContoursDemo_SOURCE
    ${FindContoursDemo_DIR}/widget.h
    ${FindContoursDemo_DIR}/widget.cpp
)
