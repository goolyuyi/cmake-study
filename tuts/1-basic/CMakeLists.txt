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

# see CMAKE_CXX_KNOWN_FEATURES
# better use, will report error if hasn't such feature
target_compile_features(hello_p1 PRIVATE cxx_std_23)

target_link_libraries(hello_p1 PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(hello_p1 PRIVATE uv_a)
target_link_libraries(hello_p1 PRIVATE Boost::filesystem)

message("BUILDSYSTEM_TARGETS:${BUILDSYSTEM_TARGETS}")
message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
message("CMAKE_ROOT:${CMAKE_ROOT}")

message("CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")

message("PROJECT_NAME:${PROJECT_NAME}")

message("CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER}")

# === play with cache & properties
set(YI_TEST "good" CACHE STRING good FORCE)
set_property(CACHE YI_TEST PROPERTY STRINGS good bad insane)
#set_directory_properties()
#set_target_properties()
#set_source_files_properties()
#set_tests_properties()

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

# === play function
function(foo name)
    # function has it's own scope
    set(test 123)
    message("foo:${name},${ARGC},${ARG1}")
endfunction()


macro(bar name)
    # macro doesn't
    set(test 123)
    message("bar:${name},${ARGC},${ARG1}")
endmacro()

foo("yuyi" ,"pony")
bar("yuyi" ,"pony")

# === play for
foreach (t AA BB CC DD)
    message("${t}")
endforeach ()

# === call cmake function
find_file(YI_MAINCPP NAMES main.cpp PATHS ${CMAKE_SOURCE_DIR})
message("${YI_MAINCPP}")

