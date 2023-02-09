cmake_minimum_required(VERSION 3.24)
project(CMakePlayground
        VERSION 1.0
        DESCRIPTION "cmake practice"
        HOMEPAGE_URL http://www.bing.com/
        LANGUAGES CXX C
        )
message("Hello Yijiang")

#cpp standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

message("=============================1-cmake-lang==================================")
add_subdirectory(1-cmake-lang)

message("=============================2-cmake-sys==================================")
add_subdirectory(2-cmake-system)

message("=============================3-project-target==================================")
add_subdirectory(3-project-target)

message("=============================4-compiler-config==================================")
add_subdirectory(4-compiler-config)
#NOTE: the subd has scopped itself!
# you can't see any thing in here
message("3_project_target_sources ${3_project_target_sources}")


message("=============================x-sanitizer==================================")
add_subdirectory(x-sanitizer)