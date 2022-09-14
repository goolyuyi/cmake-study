## Essential

```cmake
cmake_minimum_required(VERSION 3.5)
project(hello_cmake)
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

```cmake
list(APPEND CMAKE_MESSAGE_CONTEXT "top")
message("Before `foo`")
```

* `CMAKE_BUILD_PARALLEL_LEVEL`
    * `cmake --build <dir> --parallel [<number-of-jobs>]`
* `CMAKE_VERBOSE_MAKEFILE`
    * `cmake --build <dir> --verbose`
* `CMAKE_SYSTEM_NAME`
    * `CMAKE_HOST_SYSTEM`, `CMAKE_HOST_SYSTEM_NAME`, `CMAKE_HOST_SYSTEM_PROCESSOR` `CMAKE_HOST_SYSTEM_VERSION`
* `CMAKE_<LANG>_BYTE_ORDER` variable, where <LANG> is C, CXX, OBJC, or CUDA.

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
*

#### info

* `cmake_host_system_information(RESULT <VARIABLE> QUERY <KEY>…)`

#### project

```cmake
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

```cmake
add_subdirectory(source_dir [binary_dir]
        [EXCLUDE_FROM_ALL])
```

```cmake
try_run(<runResultVar> <compileResultVar>
        <bindir> <srcfile> [CMAKE_FLAGS <flags>...]
        [COMPILE_DEFINITIONS <defs>...]
        [LINK_OPTIONS <options>...]
        [LINK_LIBRARIES <libs>...]
        [COMPILE_OUTPUT_VARIABLE <var>]
        [RUN_OUTPUT_VARIABLE <var>]
        [OUTPUT_VARIABLE <var>]
        [WORKING_DIRECTORY <var>]
        [ARGS <args>...])
```

* `load_cache()`
* `set_property(TARGET <target> PROPERTY <name> <value>)`

    * `GLOBAL` `DIRECTORY` `SOURCE` `INSTALL` `TEST` `CACHE`

#### target

* `add_library(hello_library STATIC src/Hello.cpp)`
    * `STATIC`/`SHARED`/`MODULE`
    * `add_library(cars OBJECT car.cpp)`
* `add_custom_target`

* `add_custom_target`

```cmake
add_custom_target(Name [ALL] [command1 [args1...]]
        [COMMAND command2 [args2...] ...]
        [DEPENDS depend depend depend ... ]
        [BYPRODUCTS [files...]]
        [WORKING_DIRECTORY dir]
        [COMMENT comment]
        [JOB_POOL job_pool]
        [VERBATIM] [USES_TERMINAL]
        [COMMAND_EXPAND_LISTS]
        [SOURCES src1 [src2...]])
```

```cmake
add_custom_target(clean_stale_coverage_files
        COMMAND find . -name "*.gcda" -type f -delete)
```

* `add_executable(<name> ALIAS <target>)`

* `add_custom_command`

```cmake
add_custom_command(OUTPUT output1 [output2 ...]
        COMMAND command1 [ARGS] [args1...]
        [COMMAND command2 [ARGS] [args2...] ...]
        [MAIN_DEPENDENCY depend]
        [DEPENDS [depends...]]
        [BYPRODUCTS [files...]]
        [IMPLICIT_DEPENDS <lang1> depend1
        [<lang2> depend2] ...]
        [WORKING_DIRECTORY dir]
        [COMMENT comment]
        [DEPFILE depfile]
        [JOB_POOL job_pool]
        [VERBATIM] [APPEND] [USES_TERMINAL]
        [COMMAND_EXPAND_LISTS])
```

```cmake
add_custom_command(TARGET <target>
        PRE_BUILD | PRE_LINK | POST_BUILD
        COMMAND command1 [ARGS] [args1...]
        [COMMAND command2 [ARGS] [args2...] ...]
        [BYPRODUCTS [files...]]
        [WORKING_DIRECTORY dir]
        [COMMENT comment]
        [VERBATIM] [USES_TERMINAL]
        [COMMAND_EXPAND_LISTS])
```

* prop
    * `get_target_property(<var> <target> <property-name>)`
    * `set_target_properties(<target1> <target2> ... PROPERTIES <prop1-name>...) <value1>`

#### target config

* `target_compile_definitions(<source> <INTERFACE|PUBLIC|PRIVATE> [items1...])`
* `target_include_directories(target PRIVATE ${PROJECT_SOURCE_DIR}/include)`
* `target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <item>... [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)`
* `target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> [...])`
    * `cxx_std_17` `cxx_std_20` `cxx_std_23`
* `target_compile_options()`

```cmake
target_compile_options(<target> [BEFORE]
        <INTERFACE|PUBLIC|PRIVATE> [items1...]
        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

* `target_precompile_headers()`

```cmake
add_executable(precompiled hello.cpp)
target_precompile_headers(precompiled PRIVATE <iostream>)
```

* `target_include_directories`

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
        <INTERFACE|PUBLIC|PRIVATE> [item1...]
        [<INTERFACE|PUBLIC|PRIVATE> [item2...] ...])
```

#### install

* `install (TARGETS cmake_examples_inst_bin DESTINATION bin)`
* `install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)`
* `install (FILES cmake-examples.conf DESTINATION etc)`
* install:`cmake install DESTDIR=/tmp/stage`
* install:`cmake install`
* uninstall: `sudo xargs rm < install_manifest.txt`
* `target_compile_definitions(cmake_examples_compile_flags PRIVATE EX3)`
* `find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)`

#### find_package

```cmake
find_package(<PackageName> [version] [EXACT] 
        [QUIET] # no message
        [REQUIRED] [[COMPONENTS] [components...]]
        [OPTIONAL_COMPONENTS components...]
        [CONFIG|NO_MODULE]
        [GLOBAL]
        [NO_POLICY_SCOPE]
        [BYPASS_PROVIDER]
        [NAMES name1 [name2 ...]]
        [CONFIGS config1 [config2 ...]]
        [HINTS path1 [path2 ... ]] #hint path
        [PATHS path1 [path2 ... ]] #exact path
        [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH) ]
        [PATH_SUFFIXES suffix1 [suffix2 ...]]
        [NO_DEFAULT_PATH]
        [NO_PACKAGE_ROOT_PATH]
        [NO_CMAKE_PATH]
        [NO_CMAKE_ENVIRONMENT_PATH]
        [NO_SYSTEM_ENVIRONMENT_PATH]
        [NO_CMAKE_PACKAGE_REGISTRY]
        [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
        [NO_CMAKE_SYSTEM_PATH]
        [NO_CMAKE_INSTALL_PREFIX]
        [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
        [CMAKE_FIND_ROOT_PATH_BOTH |
        ONLY_CMAKE_FIND_ROOT_PATH |
        NO_CMAKE_FIND_ROOT_PATH])
```
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
