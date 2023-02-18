file(REAL_PATH ${CMAKE_CURRENT_LIST_DIR}/../yi-cmake-utils _yi_cmake_utils_path)
list(APPEND CMAKE_MODULE_PATH ${_yi_cmake_utils_path})
include(IO)

#===============================================================
# manually import a library

add_library(doglib SHARED IMPORTED)

set_target_properties(doglib PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/6-install-test-pack/fake-install/lib/lib6_yi_dog_lib.dylib)
#IMPORTED_IMPLIB for windows DLL's lib file

#IMPORTED_LOCATION_DEBUG
#IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"

target_include_directories(doglib INTERFACE ${PROJECT_SOURCE_DIR}/6-install-test-pack/fake-install/include)

add_executable(7_manual_import manual_import.cpp)
target_link_libraries(7_manual_import doglib)

#===============================================================
#[=[
consider this as a downstream project which consume the mathlib(think it maybe comes from a third party)

note: you need to build/install mathlib by a separate CLion process or manually like this:
`~/dev/CLionProjects/cmake-study/7-import-export/mathlib/cmake-build-debug> cmake --build .`
`~/dev/CLionProjects/cmake-study/7-import-export/mathlib/cmake-build-debug> cmake --install . --prefix ../../fake-install-mathlib`

#]=]


#===============================================================
#[=[
we can directly include the target
but we need many hardcode and can't use the feature of find_package()
#]=]
#include(${CMAKE_CURRENT_SOURCE_DIR}/fake-install-mathlib/lib/cmake/mathlibTargets.cmake)

#===============================================================
#[=[
we can import from the config file
there are two versions of config file, one support component
#]=]

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/fake-install-mathlib/lib/cmake)

find_package(YiMathLib_Component 0.1 REQUIRED CONFIG COMPONENTS mathlib mathutil)
#use the component version of config

#find_package(YiMathLib 0.1 REQUIRED CONFIG)
#use the no component version of config

add_executable(7_test_mathlib test_mathlib.cpp)
target_link_libraries(7_test_mathlib YiMathLib::mathlib)

add_executable(7_test_mathutil test_mathutil.cpp)
target_link_libraries(7_test_mathutil YiMathLib::mathutil)

#===============================================================
#test it
enable_testing()
add_test(NAME 7_test_mathlib COMMAND 7_test_mathlib)
add_test(NAME 7_test_mathutil COMMAND 7_test_mathutil)