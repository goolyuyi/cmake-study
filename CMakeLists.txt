cmake_minimum_required(VERSION 3.24)
project(CMakePlayground
        VERSION 1.0
        DESCRIPTION "cmake practice"
        HOMEPAGE_URL http://www.bing.com/
        LANGUAGES CXX C
        )
message("Hello Yijiang")

#set(CMAKE_DEBUG_POSTFIX d)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

#==============================================================
#CONCEPT: RPath
#
#https://dev.my-gate.net/2021/08/04/understanding-rpath-with-cmake/
#if(APPLE)
#    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
#elseif(UNIX)
#    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
#endif()

#cpp standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()

message("=============================1-cmake-lang==================================")
add_subdirectory(1-cmake-lang)

message("=============================2-cmake-sys==================================")
add_subdirectory(2-cmake-system)

message("=============================3-project-target==================================")
add_subdirectory(3-project-target)
#NOTE: the subd has scopped itself!
# you can't see any thing in here
message("3_project_target_sources ${3_project_target_sources}")

message("=============================4-compiler-config==================================")
add_subdirectory(4-compiler-config)

message("=============================5-find-package==================================")
add_subdirectory(5-find-package)

message("=============================6-install-test-export==================================")
add_subdirectory(6-install-test-pack)

message("=============================7-import-export==================================")
add_subdirectory(7-import-export)

message("=============================8-module-utils==================================")
add_subdirectory(8-module-utils)