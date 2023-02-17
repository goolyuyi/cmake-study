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
        #specified as relative paths to the CMAKE_INSTALL_PREFIX but should not explicitly include the CMAKE_INSTALL_PREFIX:
        )

install(TARGETS mathlib
        EXPORT mathlibTargets # @1
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

add_library(math_symbol INTERFACE) # a header only lib

target_include_directories(math_symbol INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/math_symbol>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/math_symbol>"
        )

install(
        TARGETS math_symbol
        EXPORT mathlibTargets
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
# and finnaly the `${_IMPORT_PREFIX}` used!


#================================================
#[=[
for now you can directly include the target in 7-import-export/CMakeLists.txt
consider it as a assemble project which consume the mathlib
#]=]


#================================================
#[=[EXPORT TO BUILD TREE
we can also export the targets in the build tree
this is useful for local development
e.g a team mate of me downloaded the mathlib project, but the lib is are very early stage
so he can debug, re-impl the lib in&with his own project
#]=]
export(EXPORT mathlibTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/mathlibTargets.cmake"
        NAMESPACE ${PROJECT_NAME}::
        )
#you can see every path in mathlibTargets.cmake under the build tree is HARDCODED!


#================================================
#GENERATE THE CONFIG FILE
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

#================================================
#let's create another lib
#so this package has 2 components(normally as exports):mathlibTargets mathutilTargets
#note: add `include("${CMAKE_CURRENT_LIST_DIR}/mathutilTargets.cmake")` to Config.cmake.in
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