#[=[
cmake can use install() to:
* install target(lib,bin) on local machine(
    * very useful for CI/CD
* generate a package for reuse
    you wrote a cmake project -> build, for debug and testing
    -> install, for downstream project reuse as library:
        * gen the config and target cmake file
        * copy files(e.g. .h)

* call cli in `buildtree`:
`cmake --install . --config Release --prefix "/home/myuser/installdir" `

* for IDE support:
`cmake --build . --target install --config Debug`

install cmd will gen some directives in `cmake_install.cmake`
#]=]
# https://cmake.org/cmake/help/latest/command/install.html#command:install


#include(GNUInstallDirs)

#==============================================
# CMAKE_INSTALL_PREFIX where to install (is the root of install tree)
# 如果不指定,cmake会自动选择(比如linux会在/usr/local）
add_library(6_yi_dog_lib SHARED ../3-project-target/dog-lib/dog-lib.cpp)
set(Export_Name 6Chapter)

target_include_directories(6_yi_dog_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../3-project-target/dog-lib/
        )

add_executable(6_welcome welcome.cpp)
target_link_libraries(6_welcome 6_yi_dog_lib)

install(TARGETS 6_welcome DESTINATION bin)
install(TARGETS 6_yi_dog_lib DESTINATION lib
        )

install(FILES data.file DESTINATION data)
install(FILES ../3-project-target/dog-lib/dog-lib.h; DESTINATION include)

#CLion目前不支持install target，只能手动执行
# `~/dev/CLionProjects/cmake-study/cmake-build-debug/6-install-test-pack> cmake --build . --install . --prefix "../../6-install-test-pack/fake-install"`

#===============================================
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

#=============================================
#TODO: cpack