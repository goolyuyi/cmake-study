#[=[ cmake can use install() to:
* install target(lib,bin) on local machine(
    * very useful for CI/CD
* generate a package for distribution

* call cli in `buildtree`:
`cmake --install . --config Release --prefix /usr/local`

* in IDE(CLion):
`cmake --build . --target install --config Debug`

#]=]
# https://cmake.org/cmake/help/latest/command/install.html#command:install

add_library(6_yi_dog_lib SHARED ../3-project-target/dog-lib/dog-lib.cpp)
target_include_directories(6_yi_dog_lib PUBLIC ../3-project-target/dog-lib)

add_executable(6_welcome welcome.cpp)

set(installable_libs 6_yi_dog_lib 6_welcome)
message("d")