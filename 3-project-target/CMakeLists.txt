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


