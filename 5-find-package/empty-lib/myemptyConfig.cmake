message("myemptyConfig.cmake called by find_package(${CMAKE_FIND_PACKAGE_NAME})")

printVars(
        CMAKE_FIND_PACKAGE_NAME
        ${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED
        ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY
)

set(${CMAKE_FIND_PACKAGE_NAME}_FOUND TRUE CACHE INTERNAL "myemptyConfig.cmake found")