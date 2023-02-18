file(REAL_PATH ${CMAKE_CURRENT_LIST_DIR}/../yi-cmake-utils _yi_cmake_utils_path)
list(APPEND CMAKE_MODULE_PATH ${_yi_cmake_utils_path})
include(IO)

printVars(CMAKE_MODULE_PATH)