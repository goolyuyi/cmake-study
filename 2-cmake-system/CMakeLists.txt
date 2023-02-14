include(../yi-cmake-utils/IO.cmake)
#=======================================
#CONCEPT:
#cmake has three stage: configure ->
#from: (input: source tree) -> [stage:configure] -> (output:build tree)
#-> [stage: generate-> build] -> (output: executable, library, archive)

#=======================================
#dir Vars
message("\n\n------working dir------")
printVars(
        CMAKE_SOURCE_DIR # The path to the top level of the source tree.
        CMAKE_CURRENT_SOURCE_DIR # The path to the source directory currently being processed.
        CMAKE_BINARY_DIR # The path to the top level of the build tree.
        CMAKE_CURRENT_BINARY_DIR) # The path to the binary directory currently being processed.
#=======================================
#list Vars
message("\n\n------list vars------")
printVars(
        #the `CMakelists.txt`
        CMAKE_CURRENT_LIST_DIR
        CMAKE_CURRENT_LIST_FILE
        CMAKE_PARENT_LIST_FILE
        CMAKE_CURRENT_LIST_LINE)

#=======================================
#os Vars
message("\n\n------os vars------")
printVars(
        CMAKE_SYSTEM_NAME
        CMAKE_HOST_SYSTEM
        CMAKE_HOST_SYSTEM_PROCESSOR
        CMAKE_HOST_SYSTEM_VERSION
)

message("\n\n------os vars2------")
printVars(
        #all are bool value
        ANDROID
        APPLE
        CYGWIN
        UNIX
        IOS
        WIN32
        WINCE
        WINDOWS_PHONE
)

message("\n\n------os vars3------")
printVars(
        #all are bool value
        CMAKE_HOST_APPLE
        CMAKE_HOST_SOLARIS
        CMAKE_HOST_UNIX
        CMAKE_HOST_WIN32
)

#=======================================
#system info
message("\n\n------system info------")
cmake_host_system_information(RESULT host_name QUERY HOSTNAME)
message("host_name ${host_name}")
#see more: OS_NAME, NUMBER_OF_LOGICAL_CORES...

#=======================================
#try run: try to compile and run a piece of code
#提前检测一些编译器特性
try_run(run_result compile_result
        ${CMAKE_CURRENT_BINARY_DIR}/test_code_1
        ${CMAKE_CURRENT_SOURCE_DIR}/_test_code/test_code_1.cpp
        )

#=======================================
#execute a cmd/process in config time
execute_process(COMMAND echo "hello world" OUTPUT_VARIABLE output)

#=======================================
#msvc info
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    printVars(CMAKE_VS_PLATFORM_TOOLSET)
endif ()

#=======================================
#config file: replace @var@ in foo.h.in with var , then copy to buildtree
option(FOO_ENABLE "Enable Foo" ON)
printVars(FOO_ENABLE)
if (FOO_ENABLE)
    set(FOO_STRING "a foo string")
endif ()
configure_file(config-file/foo.h.in foo.h)
#check `foo.h` in buildtree

add_executable(2_use_foo config-file/use_foo.cpp)
target_include_directories(2_use_foo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



