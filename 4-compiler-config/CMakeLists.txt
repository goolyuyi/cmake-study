include(../yi-cmake-utils/IO.cmake)


#=======================================
#CONCEPT: use these func to set or tweak the target
#target_compile_definitions()
#target_compile_options()
#target_include_directories()
#target_link_directories()
#target_link_options()
#target_precompile_headers()
#target_sources()

add_executable(4_compiler_config hello.cpp)

#=======================================
# * difinitions
target_compile_definitions(
        4_compiler_config PRIVATE
        FOO
        -DBAR #-D will remove
)

execute_process(COMMAND git log -1 --pretty=format:%h OUTPUT_VARIABLE SHA)
target_compile_definitions(4_compiler_config PRIVATE "SHA=${SHA}")

# * include directories
target_include_directories(4_compiler_config PRIVATE inc)

# * compiler feature
target_compile_features(4_compiler_config PRIVATE cxx_std_17) # at least C++ 17

#=======================================
#Check compiler
#CMAKE_<LANG>_COMPILER_ID
printVars(CMAKE_CXX_COMPILER_ID
        CMAKE_CXX_COMPILER_VERSION
        CMAKE_CXX_COMPILE_FEATURES)

#64bit or 32bit?
printVars(CMAKE_SIZEOF_VOID_P)

# * toolchain infos
printVars(CMAKE_GENERATOR)

printVars(CMAKE_BUILD_TYPE)

# * compiler options
#CMAKE_<LANG>_FLAGS_<CONFIG>
printVars(
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
)
#global flags, when you create a target, it will be added to the target
#but you can override it by target_compile_options()

#=================================
#EXAMPLE: if msvc
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    printVars(MSVC_VERSION)
endif ()

#=================================
#EXAMPLE: build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET 4_compiler_config PRE_BUILD
            COMMAND echo ARGS "check some pre-works for 4_compiler_config...")
endif ()

#=================================
#EXAMPLE: inspect target
printTargetProps(
        4_compiler_config
        COMPILE_DEFINITIONS
        COMPILE_FEATURES
        COMPILE_OPTIONS
        INCLUDE_DIRECTORIES
        LINK_DEPENDS
        LINK_DIRECTORIES
        LINK_LIBRARIES
        LINK_OPTIONS
        POSITION_INDEPENDENT_CODE
        PRECOMPILE_HEADERS
        SOURCES
)

#=======================================
# CONCEPT
# precompile headers
target_precompile_headers(4_compiler_config PRIVATE <iostream>)
#target_precompile_headers(<target> REUSE_FROM <other_target>)

#=======================================
# CONCEPT
# unity build
#CMAKE_UNITY_BUILD
#UNITY_BUILD
#means:
#if you have one.cpp, two.cpp
#unity build compile as `#include "one.cpp" #include "two.cpp"`
#so it compile faster in single thread but slower than parallel build

#=======================================
# ABOUT Clang
# * misc clang options
#-save-temps=obj
#-H
#-g -DNDEBUG

#=======================================
# ABOUT static lib & PIC
add_library(4_dog_lib_static STATIC ../3-project-target/dog-lib/dog-lib.cpp)
add_library(4_dog_lib_shared SHARED ../3-project-target/dog-lib/dog-lib.cpp)
#you should toggle on PIC if a static lib rely on a shared lib
#set_target_properties(dependency_target PROPERTIES POSITION_INDEPENDENT_CODE ON)


#=======================================
# Use CheckCXXSourceCompiles
# to compile a snippet of code to check if it works
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::log(1.0);
    return 0;
  }
" HAVE_LOG)
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::exp(1.0);
    return 0;
  }
" HAVE_EXP)

printVars(
        HAVE_LOG
        HAVE_EXP
)