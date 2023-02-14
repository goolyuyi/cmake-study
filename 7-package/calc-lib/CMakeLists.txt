add_library(calc SHARED calc.cpp)
#target_include_directories(calc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
#set_target_properties(calc PROPERTIES
#        PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/calc.h
#        )