cmake_minimum_required(VERSION 3.16)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
     set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
     set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2")
     set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

file(GLOB REQUIRE_FILE ${CMAKE_SOURCE_DIR}/requires.txt)
list(APPEND REQUIRE_FILES ${REQUIRE_FILE})
include(${CMAKE_SOURCE_DIR}/cmake/conangen.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/conansup.cmake)

project(OpencvFindContoursDemo VERSION LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/env.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/qtcomp.cmake)

set(ENABLE_SQLITE3 ON)
add_definitions(-DORMPP_ENABLE_SQLITE3)
include_directories(ormpp/)
include_directories(ormpp/ormpp/)
if (ENABLE_SQLITE3)
include_directories(thirdparty/sqlite3/)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/install)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
