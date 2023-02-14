
# cmake has two type of find_package
# cmake modules -- provided by cmake(fallback to config)
# package config-files -- provided by package author 
# fetch content -- like search in module but provided by FetchContent()(fallback to module)

printVars(CMAKE_PREFIX_PATH #search config path
        CMAKE_MODULE_PATH #search module path
        CMAKE_FIND_ROOT_PATH #for 're-root'
        CMAKE_FIND_PACKAGE_REDIRECTS_DIR # set by FetchContent() or user
        CMAKE_FRAMEWORK_PATH #used by macos
        CMAKE_APPBUNDLE_PATH #used by macos
        )


#you can set this to enable vcpkg
#set(CMAKE_TOOLCHAIN_FILE "/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"
#        CACHE STRING "vcpkg path")
#OR
#`cmake -B build -S. -DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake`

find_package(OpenExr REQUIRED)
printDirProps(
        ./
        BUILDSYSTEM_TARGETS
        IMPORTED_TARGETS
)


printVars(
        OpenExr_FOUND
        OpenExr_CONFIG
)

#all the var set by find_package(OpenExr)
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    if (_variableName MATCHES "OpenExr")
        message(STATUS "${_variableName}")
        message(STATUS "\t${${_variableName}}")
    endif ()
endforeach ()

#custom package
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/empty-lib)
printVars(
        CMAKE_PREFIX_PATH # set by FetchContent() or user

)

find_package(myempty REQUIRED QUIET)

printVars(myempty_FOUND)

# FetchContent
include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.zip
)


FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest yaml-cpp)

include(CMakePrintHelpers)
printTargetProps(yaml-cpp::yaml-cpp TYPE SOURCE_DIR)
printTargetProps(GTest::gtest_main TYPE SOURCE_DIR)


#
#enable_testing()
#
#add_executable(
#        5_test
#        hello_test.cpp
#)
#target_link_libraries(
#        5_test
#        GTest::gtest_main
#)
#
#include(GoogleTest)
#gtest_discover_tests(5_test)
#printDirProps(BUILDSYSTEM_TARGETS
#        IMPORTED_TARGETS
#        )
#printProps(GTest::gtest_main IMPORTED)
#



