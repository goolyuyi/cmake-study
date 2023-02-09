## Essential

```cmake
cmake_minimum_required(VERSION 3.5)
project(hello_cmake)
add_executable(hello_cmake main.cpp) #create a target
target_include_directories(Tutorial PUBLIC
        "${PROJECT_BINARY_DIR}"
        )
set(CMAKE_CXX_STANDARD 23) #set a var
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

```cmake
list(APPEND CMAKE_MESSAGE_CONTEXT "top")
message("Before `foo`")
```

* `CMAKE_BUILD_PARALLEL_LEVEL` `-j`
    * `cmake --build <dir> --parallel [<number-of-jobs>]`
* `CMAKE_VERBOSE_MAKEFILE`
    * `cmake --build <dir> --verbose`
* `CMAKE_SYSTEM_NAME`
    * `CMAKE_HOST_SYSTEM`, `CMAKE_HOST_SYSTEM_NAME`, `CMAKE_HOST_SYSTEM_PROCESSOR` `CMAKE_HOST_SYSTEM_VERSION`
* `CMAKE_<LANG>_BYTE_ORDER` variable, where <LANG> is C, CXX, OBJC, or CUDA.
* `CMAKE_MODULE_PATH` for `include()` `find_package()`

#### utils

* `${}` var or cache `$CACHE{}` cache `$ENV{}` env
* `NOT xxx` `xxx AND xxx` `xxx OR xxx`
* `YES,ON,Y,TRUE` `OFF,NO,FALSE...`
* `xxx MATCHES <regex>`
* `xxx IN_LIST <var>`
* `EXISTS <path>` `IS_DIRECTORY` `IS_SYMLINK` `IS_ABSOLUTE`

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
* `CMAKE_CXX_EXTENSIONS`
* compiler
    * `CMAKE_CXX_COMPILE_FEATURES`
        * `list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_variable_templates result)`
* optimization
    * `CMAKE_INTERPROCEDURAL_OPTIMIZATION`

#### project

* `PROJECT_NAME`
* compiler:

    * `CMAKE_C_COMPILER` - The program used to compile c code.
    * `CMAKE_CXX_COMPILER` - The program used to compile c++ code.
    * `CMAKE_LINKER` - The program used to link your binary.

### Props

* `CXX_STANDARD` on `TARGET`
* the prop on `TARGET` can use CMake command to set/get

    * `AUTOUIC_OPTIONS`
    * `COMPILE_DEFINITIONS`
    * `COMPILE_FEATURES`
    * `COMPILE_OPTIONS`
    * `INCLUDE_DIRECTORIES`
    * `LINK_DEPENDS`
    * `LINK_DIRECTORIES`
    * `LINK_LIBRARIES`
    * `LINK_OPTIONS`
    * `POSITION_INDEPENDENT_CODE`
    * `PRECOMPILE_HEADERS`
    * `SOURCES`

### Generators

`$<UPPER_CASE:$<PLATFORM_ID>>`

`LINK_LIBRARIES`
`INCLUDE_DIRECTORIES`
`COMPILE_DEFINITIONS`

### Commands

#### basic

* `message(SEND_ERROR)`
* `file()`
* `execute_process()` - run in generator stage

#### info

* `cmake_host_system_information(RESULT <VARIABLE> QUERY <KEY>…)`

#### project

* `project()`
* `add_subdirectory()`
* `try_run()` `try_compile()`
* `load_cache()` - Load in the values from another project's CMake cache.
* `set_property(TARGET <target> PROPERTY <name> <value>)`

    * `GLOBAL` `DIRECTORY` `SOURCE` `INSTALL` `TEST` `CACHE`
* `find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)`

#### target

* `add_library(hello_library STATIC src/Hello.cpp)`
    * `STATIC`/`SHARED`/`MODULE`/`OBJECT`
* `add_custom_target`

```cmake
add_custom_target(clean_stale_coverage_files
        COMMAND find . -name "*.gcda" -type f -delete)
```

* `add_executable(<name> ALIAS <target>)`
* `add_custom_command`

* prop
    * `get_target_property(<var> <target> <property-name>)`
    * `set_target_properties(<target1> <target2> ... PROPERTIES <prop1-name>...) <value1>`

### target config

* `target_compile_definitions(<source> <INTERFACE|PUBLIC|PRIVATE> [items1...])`
* `target_sources()`
* `target_include_directories(target PRIVATE ${PROJECT_SOURCE_DIR}/include)`
* `target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <item>... [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)`
* `target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> [...])`

    * `cxx_std_17` `cxx_std_20` `cxx_std_23`
* `target_compile_options()`
* `target_compile_definitions()`
* `target_precompile_headers()`

```cmake
add_executable(precompiled hello.cpp)
target_precompile_headers(precompiled PRIVATE <iostream>)
```

### install

* `install (TARGETS cmake_examples_inst_bin DESTINATION bin)`
* `install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)`
* `install (FILES cmake-examples.conf DESTINATION etc)`
* install:`cmake install DESTDIR=/tmp/stage`
* install:`cmake install`
* uninstall: `sudo xargs rm < install_manifest.txt`
* `target_compile_definitions(cmake_examples_compile_flags PRIVATE EX3)`

### CLion

* with vcpkg
* Preference->Build,Execution,Deployment->CMake->CMake option

```cmake
"-DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

* reload CMakeList.txt to 'run' the CMakeList.txt

### CMake Preset

`CMakeUserPresets.json` for developers' own local builds. This file should not be checked into VCS.

## Refs

* Why is cmake file GLOB evil? https://stackoverflow.com/questions/32411963/why-is-cmake-file-glob-evil
* Useful vars: https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables
* Object files vs Library files and
  why? https://stackoverflow.com/questions/23615282/object-files-vs-library-files-and-why

## TODO

* imgui
* godot
* folly
* blender
* json
* awesome-cpp
* project-based-learning
* https://github.com/JesseTG/awesome-qt
