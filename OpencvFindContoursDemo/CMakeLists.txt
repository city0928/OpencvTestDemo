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


set(TOOL_VERSION_NUMBER 0.1.0.1)
set(TOOL_EXE_FILENAME "opencv测试工具")
set(CMAKE_PROJECT_NAME ${TOOL_EXE_FILENAME})


file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/install)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

Set(Lib3rd)
Set(REQUIRES_PY)
file(STRINGS ${CMAKE_CURRENT_LIST_DIR}/requires.txt REQUIRES)
while(REQUIRES)
    list(POP_FRONT REQUIRES REQUIRE_STR)
    message(status "current str:" ${REQUIRE_STR})
    set(REQUIRE_PY "        self.requires(f\"${REQUIRE_STR}\", force=True)\n")
    if(NOT REQUIRE_PY IN_LIST REQUIRES_PY)
        string(REPLACE "/" ";" REQUIRE_STR_LST ${REQUIRE_STR})
        list(GET REQUIRE_STR_LST 0 REQUIRE)
        message("REQUIRE:" ${REQUIRE})
        find_package(${REQUIRE} REQUIRED)
        message(STATUS ${PROJECT_NAME} ": Require: " ${REQUIRE})

        list(APPEND Lib3rd "${REQUIRE}::${REQUIRE}")
        list(APPEND REQUIRES_PY ${REQUIRE_PY})
        unset(REQUIRE_PY)
        if(MSVC)
            set(include_path "${REQUIRE}_INCLUDE_DIRS")
            string(REPLACE "/include" "" package_path ${${include_path}})
            file(GLOB dlls_to_copy "${package_path}/*/*.dll")
            file(GLOB pdbs_to_copy "${package_path}/*/*.pdb")
            file(COPY ${dlls_to_copy} ${pdbs_to_copy} DESTINATION ${CMAKE_BINARY_DIR})
            list(APPEND LibDeploy ${dlls_to_copy})
        endif()
    endif()
endwhile()
list(JOIN REQUIRES_PY "" REQUIRES_PY)
message(STATUS  ${PROJECT_NAME} ": REQUIRES_PY: \n" ${REQUIRES_PY})

# LOCAL LIB
#set(IMGPROC_DIR "D:/guanzhaohang/desktop/LibImgProc/Debug")
#set(IMGPROC_INCLUDE_DIR ${IMGPROC_DIR}/include)
#set(IMGPROC_LIB_DIR ${IMGPROC_DIR}/lib)
#include_directories(${IMGPROC_INCLUDE_DIR})
#find_library(LO_IMGPROC LibImgProcd REQUIRED PATHS ${IMGPROC_LIB_DIR})


list(APPEND LinkLibs ${LinkLibsQt} ${Lib3rd})
message(STATUS ${PROJECT_NAME} ": LinkLibs: " ${LinkLibs})

# 子模块
include(${CMAKE_CURRENT_LIST_DIR}/src/src.cmake)
add_executable(${PROJECT_NAME}
    ${src_SOURCE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LinkLibs} ${LO_IMGPROC})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
