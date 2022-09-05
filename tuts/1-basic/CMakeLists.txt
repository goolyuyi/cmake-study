# "-DCMAKE_TOOLCHAIN_FILE=/Users/goolyuyi/dev/CLionProjects/vcpkg/scripts/buildsystems/vcpkg.cmake"

cmake_minimum_required(VERSION 3.20)

project(hello_p1)

set(SOURCES
        main.cpp
        )

find_package(Boost COMPONENTS filesystem)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(libuv CONFIG REQUIRED)

add_executable(hello_p1 ${SOURCES})

#set(CMAKE_CXX_STANDARD 23)
target_compile_features(hello_p1 PRIVATE cxx_std_23)

target_link_libraries(hello_p1 PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(hello_p1 PRIVATE uv_a)
target_link_libraries(hello_p1 PRIVATE Boost::filesystem)

message("BUILDSYSTEM_TARGETS:${BUILDSYSTEM_TARGETS}")
message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
message("CMAKE_ROOT:${${CMAKE_ROOT}}")

# === play with cache
set(YI_TEST "yyy" CACHE PATH "" FORCE)
option(YI_OPT "use the yi-opt???")

# === play with list
list(APPEND llll a b c "5555")
message("${llll}")

# === play with message
message(CHECK_START "Finding my things")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
unset(missingComponents)

message(CHECK_START "Finding partA")
# ... do check, assume we find A
message(CHECK_PASS "found")

message(CHECK_START "Finding partB")
# ... do check, assume we don't find B
list(APPEND missingComponents B)
message(CHECK_FAIL "not found")

list(POP_BACK CMAKE_MESSAGE_INDENT)
if (missingComponents)
    message(CHECK_FAIL "missing components: ${missingComponents}")
else ()
    message(CHECK_PASS "all components found")
endif ()

