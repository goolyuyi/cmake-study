cmake_minimum_required(VERSION 3.20)
project(YiMathLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)
#[=[
for CMAKE_INSTALL_<dir>
Define GNU standard installation directories:
bin
lib
sbin
etc
include
...
#]=]

add_library(mathlib STATIC mathlib.cpp)

target_include_directories(mathlib
        PUBLIC
        #only for build tree
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"

        #only for install tree
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

install(TARGETS mathlib
        EXPORT mathlibTargets # @1
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} #consume GNUInstallDirs
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

#================================================
#[=[
for a IMPORTED target:
INTERFACE_ props will propagate only if the prop name exist in COMPATIBLE_INTERFACE_STRING
e.g. `INTERFACE_INCLUDE_DIRECTORIES` will propagate because the name `INCLUDE_DIRECTORIES` exist in COMPATIBLE_INTERFACE_STRING
#]=]

install(FILES mathlib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT mathlibTargets #consume the exports @1
        FILE mathlibTargets.cmake
        NAMESPACE ${PROJECT_NAME}:: #the exported target name will be YiMathLib::mathlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        )

