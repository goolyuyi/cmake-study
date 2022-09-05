## Config
### CLion
* with vcpkg
  * Preference->Build,Execution,Deployment->CMake->CMake option
```
"-DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```



## TODO

https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables

* imgui
* godot
* folly
* blender
* json
* awesome-cpp
* project-based-learning
* https://github.com/JesseTG/awesome-qt

* cmake jetbrains
  CMakeLists.txt
CMakePresets.json for project-wise builds. This file can be shared via VCS.

CMakeUserPresets.json for developers' own local builds. This file should not be checked into VCS.

## Basic Usage

Gen

```powershell
cmake -S . -B build
# -S=source dir, -B=build dir
```

Build

```powershell
cmake --build build
```

Overwrite property

```
cmake .. -DCMAKE_BUILD_TYPE=Release
```

## In CMakeList

### essential

```
cmake_minimum_required(VERSION 3.5)
project (hello_cmake)
add_executable(hello_cmake main.cpp) #create a target
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ) 
set(CMAKE_CXX_STANDARD 11) #set a var
```

### directives(function)

* `add_library(MathFunctions mysqrt.cxx)`
    * alias:`add_library(hello::library ALIAS hello_library)`
* glob:`file(GLOB SOURCES "src/*.cpp")`
* `target_include_directories(target PRIVATE ${PROJECT_SOURCE_DIR}/include)` to pass `-I` to compiler
    * `PRIVATE` - the directory is added to this target’s include directories
    * `INTERFACE` - the directory is added to the include directories for any targets that link this library.
    * `PUBLIC` - As above, it is included in this library and also any targets that link this library.
* `add_library(hello_library STATIC src/Hello.cpp)`
    * `STATIC`/`SHARED`/`MODULE`
* `install (TARGETS cmake_examples_inst_bin DESTINATION bin)`
    * `${CMAKE_INSTALL_PREFIX}/bin`
        * default: `/usr/local/`
    * `install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)`
    * `install (FILES cmake-examples.conf DESTINATION etc)`
    * `cmake install DESTDIR=/tmp/stage` to `${DESTDIR}/${CMAKE_INSTALL_PREFIX}`
    * install:`cmake install`
    * uninstall: `sudo xargs rm < install_manifest.txt`
* `target_compile_definitions(cmake_examples_compile_flags PRIVATE EX3)` to complier define var
    * If the target was a library and the scope PUBLIC or INTERFACE has been chosen the definition would also be
      included in any executables that link this target.
    * also `set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
* `find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)`
    * TODO: detail
    * `Boost_INCLUDE_DIRS` - The path to the boost header files.

```cmake
if (Boost_FOUND)
    message("boost found")
    include_directories(${Boost_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Cannot find Boost")
endif ()

```

### vars

https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables

* `PROJECT_BINARY_DIR`
* `CMAKE_BUILD_TYPE`
    * `cmake .. -DCMAKE_BUILD_TYPE=Release`
    * Release - Adds the `-O3 -DNDEBUG` flags to the compiler
    * Debug - Adds the `-g` flag
    * MinSizeRel - Adds `-Os -DNDEBUG`
    * RelWithDebInfo - Adds `-O2 -g -DNDEBUG` flags

```cmake
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    # ONLY for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()
```

* cpp
    * `CMAKE_CXX_STANDARD`
    * `CMAKE_CXX_STANDARD_REQUIRED`
* dirs
    * `CMAKE_SOURCE_DIR`
    * `CMAKE_CURRENT_SOURCE_DIR`
    * `PROJECT_SOURCE_DIR`
    * `CMAKE_BINARY_DIR`
    * `CMAKE_CURRENT_BINARY_DIR`
    * `PROJECT_BINARY_DIR`
* proj
    * `PROJECT_NAME`
* compiler
    * `CMAKE_C_COMPILER` - The program used to compile c code.
    * `CMAKE_CXX_COMPILER` - The program used to compile c++ code.
    * `CMAKE_LINKER` - The program used to link your binary.

```cmake
# add the MathFunctions library
add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)

target_link_libraries(Tutorial PUBLIC MathFunctions)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/MathFunctions"
        )
```

## cmake cmd

* `-G Xcode` use generator
* 