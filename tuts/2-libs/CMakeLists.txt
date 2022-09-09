cmake_minimum_required(VERSION 3.20)

project(cmake-play2)

#BUILD_SHARED_LIBS
add_library(yi-lib SHARED)
target_sources(yi-lib PUBLIC yi-lib/yilib.cpp yi-lib/include/yilib.h)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} yi-lib)
target_include_directories(${PROJECT_NAME} PRIVATE yi-lib/include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

#same thing
get_property(${PROJECT_NAME}_cpp_std TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD)
message("${PROJECT_NAME}_cpp_std:${${PROJECT_NAME}_cpp_std}")

#same thing
get_target_property(${PROJECT_NAME}_cpp_std ${PROJECT_NAME} CXX_STANDARD)
message("${PROJECT_NAME}_cpp_std:${${PROJECT_NAME}_cpp_std}")

# TODO
#get_target_property(llll ${PROJECT_NAME} LINK_OPTIONS)
#message("llll: ${llll}")

#define the pre processor
target_compile_definitions(${PROJECT_NAME} PUBLIC FOO)





