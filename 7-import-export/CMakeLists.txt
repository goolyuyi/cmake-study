#===============================================================
# manually import a library

add_library(doglib SHARED IMPORTED)

set_target_properties(doglib PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/6-install-test-pack/fake-install/lib/lib6_yi_dog_lib.dylib)
#IMPORTED_IMPLIB for windows DLL's lib file

#IMPORTED_LOCATION_DEBUG
#IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"

target_include_directories(doglib INTERFACE ${PROJECT_SOURCE_DIR}/6-install-test-pack/fake-install/include)

add_executable(7_manual_import manual_import.cpp)
target_link_libraries(7_manual_import doglib)

#===============================================================

