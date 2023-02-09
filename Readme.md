# TERMINOLOGY

## cmake struct

### source tree

where your source you put...
(aka: project root)

### build tree

cmake configured to...

### listfile

aka CMakeLists.txt

### CMakeCache.txt

cmake cache

### cmake config-file

* contain information regarding how to use the library
  binaries, headers, and helper tools. Sometimes, they expose CMake macros to use in
  your project.
* `find_package()`
* `<PackageName>-config.cmake` and `<PackageName>Config.cmake`
    * `<Config>Version.cmake`

### CMakePresets

override cmake's default behavior
include cache, build, install, test, and package presets

### script

a `.cmake` can be included/add_subdirectory/executed by cmake

### modules

a cmake util package

`include (TestBigEndian)`

### Find-modules

a module can find a cpp lib in your os

`FindCURL`

### toolchain:

a toolchain consists of all of the tools used in building and running
the application
`CXX_STANDARD`

## project

* project:
* target:
* property:
* config:
* cmake var:
  var:
  cache:
  env:
* generator:

* build system:
