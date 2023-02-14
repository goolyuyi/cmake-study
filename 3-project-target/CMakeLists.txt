include(../yi-cmake-utils/IO.cmake)

#=======================================
#project Vars
message("------project vars------")
printVars(
        PROJECT_SOURCE_DIR #last place call project()
        PROJECT_BINARY_DIR
        PROJECT_NAME
        PROJECT_VERSION
        #all these will be set: <project-name>_SOURCE_DIR, <project-name>_BINARY_DIR, etc...
        CMakePlayground_SOIURCE_DIR
)

#=======================================
#CONCEPT: cmake has three type of target:
# add_executable()
# add_library()
# add_custom_target(): a pure logical target, can run some command in build time

add_executable(3_project_target main.cpp)
target_sources(3_project_target PRIVATE cat/cat.cpp)

set_target_properties(3_project_target PROPERTIES CXX_STANDARD 20)
target_link_libraries(3_project_target PUBLIC 3_project_target_dog_lib) #order doesn't matter

add_library(3_project_target_dog_lib dog-lib.cpp)

add_custom_target(3_project_target_echo_something ALL COMMAND echo "YI_PATH" $ENV{YI_PATH})

#=======================================
#CONCEPT:
#cmake's target has dependency relationship
#cmake will:
#* auto resolve by calling the `target_link_libraries`
#* manually resolve by calling the `add_dependencies`

add_dependencies(3_project_target 3_project_target_echo_something)

#=======================================
#CONCEPT:
#cmake's target's properties propagate/inherent by dependency relationship

target_compile_definitions(3_project_target_dog_lib PUBLIC
        FOO_FLAG)

#so what's the FOO_FLAG in 3_project_target? it depends on the propagation type(PUBLIC, PRIVATE, INTERFACE):
#* PUBLIC: 3_project_target_dog_lib and 3_project_target will have FOO_FLAG
#* PRIVATE: only 3_project_target_dog_lib will have FOO_FLAG
#* INTERFACE: only 3_project_target will have FOO_FLAG

#=======================================
#EXAMPLE: so we can make a dumb target, only for propagate some properties to other target!
add_library(dumb_warning_props INTERFACE)
target_compile_options(dumb_warning_props INTERFACE
        /Wall
        )
#NOTE: debug here, the prop INTERFACE_COMPILE_OPTION will be set
target_link_libraries(3_project_target PUBLIC dumb_warning_props)


#=======================================
#CONCEPT:
#* ALL is a special target, which means when `cmake --build`, it'll build all target
# except any target marked with `EXCLUDE_FROM_ALL的`

#* clean is a special target

#=======================================
#CONCEPT:
#different from add_custom_target(), this won't create a logical target(won't show in the target list)
add_custom_command(
        TARGET 3_project_target_echo_something
        PRE_BUILD #or PRE_LINK, POST_BUILD
        COMMAND echo ARGS "$ENV{PATH}" > "aaa.txt"
        DEPENDS aaa.txt #if aaa.txt is not exist(in the buildtree), this command will be run
)

#the test of dog-lib
add_executable(3_test_dog_lib dog-lib/dog-test.cpp)
target_link_libraries(3_test_dog_lib PUBLIC 3_project_target_dog_lib)

#if we wanna test dog-lib before build 3_project_target
add_custom_command(
        TARGET 3_project_target PRE_BUILD
        COMMAND $<TARGET_FILE:3_test_dog_lib>
        BYPRODUCTS 3_project_target_dog_lib
)


#=======================================
#CONCEPT:
#cmake generator expression
#it'll be evaluated at generator time when you call `cmake --build`
#so after configure, you can't see the result of generator expression
#syntax:$<XXX:arg1 arg2...>
# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html
#
#$<CONFIG>
#$<TARGET_FILE:target>
#$<TARGET_FILE_DIR:target>
#$<TARGET_PROPERTY:target,prop>
#
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


#=======================================
#EXAMPLE: the way we can get the value of generator expression
#because custom target will run at generator time
add_custom_target(3_write_some_gen_exp_to_file COMMAND ${CMAKE_COMMAND} -E echo "<TARGET_FILE:3_test_dog_lib> $<TARGET_FILE:3_test_dog_lib>")

#=======================================
#EXAMPLE: inspect some props of target
printTargetProps(
        3_project_target
        LINK_LIBRARIES
        SOURCES
        MANUALLY_ADDED_DEPENDENCIES
)

printTargetProps(
        dumb_warning_props
        INTERFACE_COMPILE_OPTIONS
)