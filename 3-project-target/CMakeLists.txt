include(../yi-cmake-utils/IO.cmake)

#project
message("------project vars------")
printVars(PROJECT_SOURCE_DIR
        PROJECT_BINARY_DIR
        PROJECT_NAME
        CMakePlayground_VERSION
        PROJECT_VERSION
        )

# * Variable changes are isolated to the nested scope.
# * You're free to configure the nested artifacts however you like.
# * Changing the nested CMakeLists.txt file doesn't require building unrelated targets.
# * Paths are local to the directory, and they can even be added to the parent include path if desired.
add_executable(3_project_target main.cpp)
set(3_project_target_sources cat.cpp)
target_sources(3_project_target PRIVATE ${3_project_target_sources})

#break point here!
set_property(TARGET 3_project_target PROPERTY CXX_STANDARD 20)
#see more: GLOBAL DIRECTORY TARGET SOURCE INSTALL CACHE level of properties

target_link_libraries(3_project_target PUBLIC 3_project_target_dog_lib)

#library target
add_library(3_project_target_dog_lib dog-lib.cpp)

#build time target
#run in build time
add_custom_target(3_project_target_echo_something ALL COMMAND echo "YI_PATH" $ENV{YI_PATH})

#make sure when build 3_project_target the echo_something will run first
#cmake will resolve all the dependencies!
add_dependencies(3_project_target 3_project_target_echo_something)
#NOTE you must 'build' target here, it's only do staff in build time!

target_compile_definitions(3_project_target_dog_lib PUBLIC
        FOO_FLAG)
#so what's the FOO_FLAG in 3_project_target_dog_lib?
#so what's the FOO_FLAG in 3_project_target?
#PUBLIC: 3_project_target_dog_lib and 3_project_target will have FOO_FLAG
#PRIVATE: only 3_project_target_dog_lib will have FOO_FLAG
#INTERFACE: only 3_project_target will have FOO_FLAG
#NOTE: all these propagate rely on dependency such as link_libraries() or add_dependencies()


#a dumb target
add_library(dumb_warning_props INTERFACE)
target_compile_options(dumb_warning_props INTERFACE
        /Wall
        )
#NOTE: debug here, the prop INTERFACE_COMPILE_OPTION will be set
target_link_libraries(3_project_target INTERFACE dumb_warning_props)

#these below are all call set_property internally
#set_target_properties()
#target_xxxx()

#you can use these keywords:
#AUTOUIC_OPTIONS
#COMPILE_DEFINITIONS
#COMPILE_FEATURES
#COMPILE_OPTIONS
#INCLUDE_DIRECTORIES
#LINK_DEPENDS
#LINK_DIRECTORIES
#LINK_LIBRARIES: target_link_libraries()
#LINK_OPTIONS
#POSITION_INDEPENDENT_CODE
#PRECOMPILE_HEADERS
#SOURCES: target_sources()

#ALL is a special target, which means when `cmake --build`, it'll build all target
#except any target marked with `EXCLUDE_FROM_ALL的`
#when add_executable() or add_library() and etc...

#different from add_custom_target(), this won't create a logical target
add_custom_command(
        TARGET 3_project_target_echo_something
        PRE_BUILD #PRE_LINK, POST_BUILD
        COMMAND echo ARGS "$ENV{PATH}" > "aaa.txt"
        DEPENDS aaa.txt
)

#the test of dog-lib
add_executable(3_test_dog_lib dog-test.cpp)
target_link_libraries(3_test_dog_lib PUBLIC 3_project_target_dog_lib)

#if we wanna test dog-lib before build 3_project_target
add_custom_command(
        TARGET 3_project_target PRE_BUILD
        COMMAND $<TARGET_FILE:3_test_dog_lib>
        BYPRODUCTS 3_project_target_dog_lib
)

#if we want something before cmake build, we can use generator expression $<XXX:arg1 arg2...>
#$<CONFIG>
#$<TARGET_FILE:target>
#$<TARGET_FILE_DIR:target>
#$<TARGET_PROPERTY:target,prop>
#
#$<UPPER_CASE:str>
#$<IF:condition,true_str,false_str>
#$<condition:true_str>
#$<NOT:arg>
#$<AND:arg1 arg2...>
#$<OR:arg1 arg2...>
#$<BOOL:str> convert to bool
#$<STREQUAL:str1,str2>
#$<EQUAL:arg1,arg2>
#$<IN_LIST:arg,list>

add_custom_target(3_write_some_gen_exp_to_file COMMAND ${CMAKE_COMMAND} -E echo "<TARGET_FILE:3_test_dog_lib> $<TARGET_FILE:3_test_dog_lib>")