include(../yi-cmake-utils/IO.cmake)

add_executable(4_compiler_config hello.cpp)

# * difinitions
target_compile_definitions(
        4_compiler_config PRIVATE
        FOO
        -DBAR #-D will remove
)

execute_process(COMMAND git log -1 --pretty=format:%h OUTPUT_VARIABLE SHA)
target_compile_definitions(4_compiler_config PRIVATE "SHA=${SHA}")

# * include directories
#used as `#include <calc.h>`
#NOTE useful for include a library
target_include_directories(4_compiler_config PRIVATE inc)

# * compiler feature
#Compiler mode is at least C++ 17
target_compile_features(4_compiler_config PRIVATE cxx_std_17)

#CMAKE_<LANG>_COMPILER_ID
printVars(CMAKE_CXX_COMPILER_ID
        CMAKE_CXX_COMPILER_VERSION
        CMAKE_CXX_COMPILE_FEATURES)

#64bit or 32bit?
printVars(CMAKE_SIZEOF_VOID_P)

# * toolchain infos
printVars(CMAKE_GENERATOR)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    printVars(MSVC_VERSION)
endif ()

printVars(CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET 4_compiler_config PRE_BUILD
            COMMAND echo ARGS "check some pre-works for 4_compiler_config...")
endif ()

# * compiler options
#CMAKE_<LANG>_FLAGS_<CONFIG>
#the global compiler option
printVars(CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(4_compiler_config PRIVATE -Wall )
#    target_compile_options(4_compiler_config PRIVATE -fsanitize=address)
endif ()

printTargetProps(4_compiler_config COMPILE_OPTIONS COMPILE_FLAGS COMPILE_DEFINITIONS)

# * precompile headers
target_precompile_headers(4_compiler_config PRIVATE <iostream>)
#target_precompile_headers(<target> REUSE_FROM <other_target>)

# * unity build
#CMAKE_UNITY_BUILD
#UNITY_BUILD
#means:
#if you have one.cpp, two.cpp
#unity build compile as `#include "one.cpp" #include "two.cpp"`
#so it compile faster in single thread but slower than parallel build

# * misc clang options
#-save-temps=obj
#-H
#-g -DNDEBUG

# * static lib
add_library(4_dog_lib_static STATIC ../3-project-target/dog-lib.cpp)
add_library(4_dog_lib_shared SHARED ../3-project-target/dog-lib.cpp)
#NOTE: you should toggle on PIC if a static lib rely on a shared lib
#set_target_properties(dependency_target PROPERTIES POSITION_INDEPENDENT_CODE ON)

