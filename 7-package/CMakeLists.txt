add_subdirectory(calc-lib)

set(EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake-export")

export(TARGETS calc
        FILE "${EXPORT_DIR}/CalcTargets.cmake"
        NAMESPACE Calc::
        )
#you can see the CalcTargets.cmake file in the build directory
#NOTE: the path is hard coded in CalcTargets.cmake


#[=[
* install(TARGETS): This installs output artifacts such as libraries and executables.
* install(FILES|PROGRAMS): This installs individual files and sets their permissions.
* install(DIRECTORY): This installs whole directories.
* install(SCRIPT|CODE): This runs a CMake script or a snippet during installation.
* install(EXPORT): This generates and installs a target export file.
#]=]

#install cmd will gen some directives in `cmake_install.cmake`

#[=[
DESTINATION: will prepend with CMAKE_INSTALL_PREFIX
PERMISSIONS:
CONFIGURATIONS: Debug,Release, MinSizeRel, RelWithDebInfo
OPTIONAL: if the file does not exist, the install command will not fail
#]=]

include(GNUInstallDirs)

install(TARGETS calc EXPORT CalcTargets
        )
#export(EXPORT CalcTargets FILE "${EXPORT_DIR}/CalcTargets.cmake" NAMESPACE Calc::)

install(EXPORT CalcTargets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        NAMESPACE Calc::
        )

#CALL THIS UNDER BUILDTREE:
#`cmake --install 7-packag  --prefix ../fake-install`