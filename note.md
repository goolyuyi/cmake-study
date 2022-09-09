## Essential

```
cmake_minimum_required(VERSION 3.5)
project (hello_cmake)
add_executable(hello_cmake main.cpp) #create a target
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ) 
set(CMAKE_CXX_STANDARD 11) #set a var
```

## Notes

### Vars

#### cmake

* `CMAKE_BUILD_TYPE`: = Debug, Release, MinSizeRel, or
  RelWithDebInfo.
* `CMAKE_MESSAGE_LOG_LEVEL` = ERROR, WARNING, NOTICE, STATUS,
  VERBOSE, DEBUG, or TRACE
* `CMAKE_MESSAGE_CONTEXT` string:
    * like `[some.context.example] Debug message.`

```
list(APPEND CMAKE_MESSAGE_CONTEXT "top")
message("Before `foo`")
```

* `CMAKE_BUILD_PARALLEL_LEVEL`
    * `cmake --build <dir> --parallel [<number-of-jobs>]`
* `CMAKE_VERBOSE_MAKEFILE`
    * `cmake --build <dir> --verbose`

#### path

* `.cmake` file path:
    * `CMAKE_CURRENT_LIST_DIR`
    * `CMAKE_CURRENT_LIST_FILE`
    * `CMAKE_PARENT_LIST_FILE`
    * `CMAKE_CURRENT_LIST_LINE`
* source path & build path:
    * `CMAKE_BINARY_DIR`
    * `CMAKE_SOURCE_DIR`
    * `CMAKE_CURRENT_BINARY_DIR`
    * `CMAKE_CURRENT_SOURCE_DIR`

#### cpp

* `CMAKE_CXX_STANDARD`
* `CMAKE_CXX_STANDARD_REQUIRED`

#### project

* `PROJECT_NAME`

* compiler:
    * `CMAKE_C_COMPILER` - The program used to compile c code.
    * `CMAKE_CXX_COMPILER` - The program used to compile c++ code.
    * `CMAKE_LINKER` - The program used to link your binary.

### Props

### Directives

* `target_include_directories(target PRIVATE ${PROJECT_SOURCE_DIR}/include)`
* `add_library(hello_library STATIC src/Hello.cpp)`
    * `STATIC`/`SHARED`/`MODULE`
* install
    * `install (TARGETS cmake_examples_inst_bin DESTINATION bin)`
    * `install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)`
    * `install (FILES cmake-examples.conf DESTINATION etc)`
    * install:`cmake install DESTDIR=/tmp/stage`
    * install:`cmake install`
    * uninstall: `sudo xargs rm < install_manifest.txt`

* `target_compile_definitions(cmake_examples_compile_flags PRIVATE EX3)`
* `find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)`

### CLion

* with vcpkg
    * Preference->Build,Execution,Deployment->CMake->CMake option

```
"-DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

* reload CMakeList.txt to 'run' the CMakeList.txt

### CMake Preset

`CMakeUserPresets.json` for developers' own local builds. This file should not be checked into VCS.

## Refs

* Why is cmake file GLOB evil? https://stackoverflow.com/questions/32411963/why-is-cmake-file-glob-evil
* Useful vars: https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables

## TODO

* imgui
* godot
* folly
* blender
* json
* awesome-cpp
* project-based-learning
* https://github.com/JesseTG/awesome-qt
