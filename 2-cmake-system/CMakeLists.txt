include(../yi-cmake-utils/IO.cmake)

#dirs

message("\n\n------working dir------")
printVars(
        CMAKE_SOURCE_DIR CMAKE_CURRENT_SOURCE_DIR
        CMAKE_BINARY_DIR CMAKE_CURRENT_BINARY_DIR)

message("\n\n------list vars------")
printVars(
        CMAKE_CURRENT_LIST_DIR
        CMAKE_CURRENT_LIST_FILE
        CMAKE_PARENT_LIST_FILE
        CMAKE_CURRENT_LIST_LINE)

##system vars
message("\n\n------os vars------")
printVars(CMAKE_SYSTEM_NAME CMAKE_HOST_SYSTEM CMAKE_HOST_SYSTEM_PROCESSOR CMAKE_HOST_SYSTEM_VERSION)

message("\n\n------os vars2------")
printVars(ANDROID APPLE CYGWIN UNIX IOS WIN32 WINCE WINDOWS_PHONE)

message("\n\n------os vars3------")
printVars(CMAKE_HOST_APPLE CMAKE_HOST_SOLARIS CMAKE_HOST_UNIX CMAKE_HOST_WIN32)

#system info
cmake_host_system_information(RESULT host_name QUERY HOSTNAME)
#see more: OS_NAME, NUMBER_OF_LOGICAL_CORES...
message("host_name ${host_name}")

#try run
try_run(run_result compile_result
        ${CMAKE_CURRENT_BINARY_DIR}/test_code_1
        ${CMAKE_CURRENT_SOURCE_DIR}/_test_code/test_code_1.cpp
        )

#execute in config time
execute_process(COMMAND echo "hello world" OUTPUT_VARIABLE output)

message("CMAKE_VS_PLATFORM_TOOLSET: ${CMAKE_VS_PLATFORM_TOOLSET}")