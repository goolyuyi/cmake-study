#[=[ cmake can use install() to:
* install target(lib,bin) on local machine(
    * very useful for CI/CD
* generate a package for distribution

* call cli in `buildtree`:
`cmake --install . --config Release --prefix "/home/myuser/installdir" `

* in IDE(CLion):
`cmake --build . --target install --config Debug`

install cmd will gen some directives in `cmake_install.cmake`

#]=]
# https://cmake.org/cmake/help/latest/command/install.html#command:install

#include(GNUInstallDirs)

#==============================================
# CMAKE_INSTALL_PREFIX where to install (is the root of install tree)
# 如果不指定,cmake会自动选择(比如linux会在/usr/local）
add_library(6_yi_dog_lib SHARED ../3-project-target/dog-lib/dog-lib.cpp)

target_include_directories(6_yi_dog_lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../3-project-target/dog-lib/>
        $<INSTALL_INTERFACE:include>
        )

add_executable(6_welcome welcome.cpp)
target_link_libraries(6_welcome 6_yi_dog_lib)

set(installable_libs 6_yi_dog_lib)
install(TARGETS 6_welcome DESTINATION bin)
install(TARGETS ${installable_libs} DESTINATION lib
        EXPORT Chapter6Targets #EXPORT: will used in cmake target file gen&install
        )

install(FILES data.file DESTINATION data)
install(FILES api.h; DESTINATION include)
install(FILES ../3-project-target/dog-lib/dog-lib.h; DESTINATION include)

#CLion目前不支持install target，只能手动执行
# `~/dev/CLionProjects/cmake-study/cmake-build-debug/6-install> cmake --build . --install . --prefix "../../fake-install"`


set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(6_welcome PRIVATE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
        )

install(EXPORT Chapter6Targets
        FILE Chapter6Targets.cmake
        DESTINATION cmake/
        )

include(CMakePackageConfigHelpers)
# generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/Chapter6Config.cmake"
        INSTALL_DESTINATION "cmake/"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/Chapter6ConfigVersion.cmake"
        VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/Chapter6Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Chapter6ConfigVersion.cmake
        DESTINATION cmake/
        )

#If we want our project to also be used from a build directory we only have to add the following to the bottom of the top level CMakeLists.txt:
export(EXPORT Chapter6Targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/Chapter6Targets.cmake"
        )

#ctest -N(must in the buildtree)
#ctest -C Debug -VV

enable_testing()
add_test(NAME Test1 COMMAND 6_welcome)
set_tests_properties(Test1
        PROPERTIES PASS_REGULAR_EXPRESSION "husky"
        )

add_test(NAME Test2 COMMAND echo 666)
set_tests_properties(Test2
        PROPERTIES PASS_REGULAR_EXPRESSION "666"
        )