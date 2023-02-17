#======================================================================
#[=[
cmake有以下3种查找包的方式：
1. find_package() :标准包管理
    * won't fail cmake process, instead return a Result variables allow the project to customize its own behavior
    according to whether the package or specific components were found.

2. FetchContent module: 从网络下载包
    *
3. FindPkgConfig: legacy
#]=]
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html

#======================================================================
#[=[
find_package()

BASIC USAGE:
```
find_package(Catch2)
find_package(GTest REQUIRED)
find_package(Boost 1.79 COMPONENTS date_time)
```

MODES:
* config mode: find the config files -- the config file must be provided by package itself
(cmake can create these when you build and install the package)

* module mode:if a package can't provide a config file,
 a find module file can be provided separately, either by the project or by CMake.
    * can easily become out-of-date.

#]=]

#======================================================================
#[=[
config mode of find_package():
* find_package search place: <prefix>+<sub>+<filename>
https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure

* <prefix>:
    * <PackageName>_ROOT
    * <PackageName>_DIR (exactly position)
    * CMAKE_PREFIX_PATH (cmake var or env)
    * CMake known locations(such as /usr/local, c:/Program Files)
* <sub>:
    * lib/cmake/<PackageName> or cmake/<PackageName>

* <filename>:
    * <PackageName>Config.cmake or <LowercasePackageName>-config.cmake
        * commonly a config file will use include() to the target files

    * <PackageName>ConfigVersion.cmake or <LowercasePackageName>-config-version.cmake
        * determine whether the version of the package satisfies(constraint)

* <target files>:
    will be included by the config file, or you can include it manually

    * <PackageName>Targets.cmake
    * <PackageName>Targets-<version>.cmake
#]=]

#======================================================================
#[=[
module mode for find_package():

1. search from: CMAKE_MODULE_PATH
2. `list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")`
3. then call `find_package(SomePackage)` will call `FindSomePackage.cmake` in module path

#]=]
#======================================================================
#you can set this to enable vcpkg
#set(CMAKE_TOOLCHAIN_FILE "/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"
#        CACHE STRING "vcpkg path")
#OR
#`cmake -B build -S. -DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake`

#======================================================================
message("----------example of find_package()----------")
printVars(CMAKE_PREFIX_PATH
        )

#note: vcpkg should use uppercase for package name
find_package(OPENEXR REQUIRED)

printDirProps(
        ./
        BUILDSYSTEM_TARGETS
        IMPORTED_TARGETS
)

printVars(
        OPENEXR_FOUND
        OPENEXR_CONFIG
)

#all the var set by find_package(OpenExr)
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    string(TOUPPER ${_variableName} _variableName_upper)
    if (_variableName_upper MATCHES "OPENEXR")
        message(STATUS "${_variableName}")
        message(STATUS "\t${${_variableName}}")
    endif ()
endforeach ()

printTargetProps(OpenEXR::OpenEXRCore IMPORTED)
printTargetProps(OpenEXR::OpenEXR IMPORTED)


#======================================================================
message("----------example of how find_package works----------")
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/empty-lib)
printVars(
        CMAKE_PREFIX_PATH # set by FetchContent() or user
)

find_package(myempty 1.2.3 EXACT REQUIRED QUIET)

printVars(myempty_FOUND)

#======================================================================
#[=[
FetchContent:
* FetchContent_Declare: declare a new FetchContent
* FetchContent_MakeAvailable: download and build the content

why two step? because it need of dependency resolution

* easy for header-only libraries
* will auto call `find_package()` for you
see: FETCHCONTENT_TRY_FIND_PACKAGE_MODE


#]=]

#======================================================================
#

message("----------example of how find_package works----------")

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(CMakePrintHelpers)

printTargetProps(GTest::gtest_main TYPE SOURCE_DIR)

#======================================================================
#[=[
Dependency Providers:
* intercept the find_package() call and FetchContent_MakeAvailable() call

https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#id11

#]=]