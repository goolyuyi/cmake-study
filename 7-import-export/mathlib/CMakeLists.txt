#consider this cmake file as a separate project, like some coder's made it
#so we will use it as a library

cmake_minimum_required(VERSION 3.20)
project(YiMathLib
        VERSION 1.2.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)
#[=[
for CMAKE_INSTALL_<dir>
Define GNU standard installation directories:
bin
lib
sbin
etc
include
...
#]=]

add_library(mathlib STATIC mathlib.cpp)

target_include_directories(mathlib
        PUBLIC
        #only for build tree
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"

        #only for install tree
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        #When defining the interface of a target for EXPORT, keep in mind that the include directories should be
        #specified as relative paths to the CMAKE_INSTALL_PREFIX but should not explicitly include the CMAKE_INSTALL_PREFIX
        #so this form is wrong: `${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}`
        )

install(TARGETS mathlib
        EXPORT mathlibTargets # @1 the exports name
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} #consume GNUInstallDirs
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

#================================================
#[=[
for a IMPORTED target:
INTERFACE_ props will propagate only if the prop name exist in COMPATIBLE_INTERFACE_STRING
e.g. `INTERFACE_INCLUDE_DIRECTORIES` will propagate because the name `INCLUDE_DIRECTORIES` exist in COMPATIBLE_INTERFACE_STRING
#]=]

install(FILES mathlib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT mathlibTargets #consume the exports @1
        FILE mathlibTargets.cmake
        NAMESPACE ${PROJECT_NAME}:: #the exported target name will be YiMathLib::mathlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        )


#================================================
# for now the mathlibTargets only has one target, We can add another one:

add_library(math_symbol INTERFACE)
# a header only lib

target_include_directories(math_symbol INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/math_symbol>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/math_symbol>"
        )

install(
        TARGETS math_symbol
        EXPORT mathlibTargets
        #it's able and commonly add multiple targets to the same exports
        #so the mathlibTargets.cmake will have 2 targets: mathlib math_symbol
)

install(FILES math_symbol/math_symbol.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/math_symbol)


#================================================
#[=[CHECK THE EXPORTED TARGETS
# Create imported target YiMathLib::mathlib
add_library(YiMathLib::mathlib STATIC IMPORTED)

set_target_properties(YiMathLib::mathlib PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include;${_IMPORT_PREFIX}/include"
        )

# Create imported target YiMathLib::math_symbol
add_library(YiMathLib::math_symbol INTERFACE IMPORTED)

set_target_properties(YiMathLib::math_symbol PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "/math_symbol;${_IMPORT_PREFIX}/include/math_symbol"
        )
#]=]

# we can see the code above in `mathlibTargets.cmake` after install
# it's relocatable because no path depend on the build tree(only the install tree)
# and the `${_IMPORT_PREFIX}` is used, means the exported targets are path location free


#================================================

#[=[
for now you can directly include the target in 7-import-export/CMakeLists.txt
#]=]

#================================================

#[=[EXPORT TO BUILD TREE
we can also export the targets in the build tree
* this is useful for local development
* e.g a team mate of mine downloaded the mathlib project, but the lib is are in very early stage
so he can build in his local, then debug, develop the lib in/with his own project
#]=]
export(EXPORT mathlibTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/mathlibTargets.cmake"
        NAMESPACE ${PROJECT_NAME}::
        )
#you can see every path in mathlibTargets.cmake under the build tree is HARDCODED!
#so this is not relocatable

#================================================
#GENERATE THE CONFIG FILE
#without the config file, we can't use find_package() to find the lib, and will lead to:
#* hardcoded path(find_package can search)
#* no version check
#* no component
#* no succeed check

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLibConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLibConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLibConfigVersion.cmake"
        COMPATIBILITY AnyNewerVersion
)

#[=[
you can see: YiMathLibConfig.cmake YiMathLibConfigVersion.cmake
generated from Config.cmake.in
#]=]

#================================================
#let's create another lib
#so this package has 2 components(normally as exports):mathlibTargets mathutilTargets
#note: added `include("${CMAKE_CURRENT_LIST_DIR}/mathutilTargets.cmake")` to Config.cmake.in
add_library(mathutil STATIC mathutil.cpp)
target_include_directories(mathutil INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )
target_link_libraries(mathutil PUBLIC math_symbol)

install(TARGETS mathutil EXPORT mathutilTargets)

install(
        EXPORT mathutilTargets
        FILE mathutilTargets.cmake
        NAMESPACE ${PROJECT_NAME}:: #the exported target name will be YiMathLib::mathlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

install(FILES mathutil.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#================================================
# to support find_package(COMPONENT) feature
# let's create another version of config file


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config_Component.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLib_ComponentConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
        NO_CHECK_REQUIRED_COMPONENTS_MACRO # we'll check it manually!
        )
#we use another config template:Config_Component.cmake.in
#it read the YiMathLib_Component_FIND_COMPONENTS vars
#and disabled check_required_components() macro

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLib_ComponentConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLib_ComponentConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/YiMathLib_ComponentConfigVersion.cmake"
        COMPATIBILITY AnyNewerVersion
)

#================================================
#[=[
let's make things complicated
we introduce a new dependency, if the OpenEXR is found, we'll add some extra features

it's needed to add these in Config.cmake.in and Config_Component.cmake.in:
```
include(CMakeFindDependencyMacro)
find_dependency(OPENEXR)
```

if the lib build with OpenEXR, the config file need to `find_package(OPENEXR)` to find the dependency
this is done by find_dependency() macro

#]=]
find_package(OPENEXR)
if (OPENEXR_FOUND)
    message(STATUS "OpenEXR found")
    target_compile_definitions(mathutil PRIVATE OPENEXR_FOUND)
    target_link_libraries(mathutil PUBLIC OpenEXR::OpenEXR OpenEXR::OpenEXRCore)
endif ()


#[=[
summary:
* at last, we have 2 logical exports: mathlibTargets; mathutilTargets
* for mathlibTargets, there are 2 targets explicit: YiMathLib::mathlib; YiMathLib::math_symbol
* for mathutilTargets, there is 1 target explicit: YiMathLib::mathutil
    * YiMathLib::mathutil depends on YiMathLib::math_symbol, so it's needed to import from mathlibTargets.cmake(little wired)
    * YiMathLib::mathutil depends on OpenEXR(if found),
    so it's needed the downstream project also can find OpenEXR in their place(maybe installed by vcpkg e.g.)

* we have two version of config file:
    * YiMathLibConfig.cmake YiMathLibConfigVersion.cmake
        * use find_package(), it'll import all the targets(mathlibTargets; mathutilTargets)

    * YiMathLib_ComponentConfig.cmake YiMathLib_ComponentConfigVersion.cmake
        * use find_package(COMPONENTS), it'll import the targets you need

* this package is like a large project(e.g. boost)
    * it has many components, you can use it separately;
    * it has external dependencies, so you need to offer them in your place(in c++ world there is no dependencies management and resolve)

* this package has a version: 1.2.3
    * if the downstream project ask version from 0.0.0 to 1.2.3, it's compatible
YiMathLib::
mathlibTargets
#]=]