cmake_minimum_required(VERSION 3.0)

# project configuration
project(appbricks VERSION 0.1 LANGUAGES CXX)
add_library(appbricks INTERFACE)

# compiler settings
if (DEV_MODE)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -Wall -Wpedantic -Wextra")
endif()

# set installation related variables
include(scripts/InstallDirHelpers.cmake)

# submodules settings
add_subdirectory(code/text)
add_subdirectory(code/core)

target_link_libraries(textbrick)
target_link_libraries(corebrick)

# create a appbricks_version.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/appbricks_version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# installation
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/appbricks)

install(TARGETS  appbricks
        EXPORT   appbricks_targets
        RUNTIME  DESTINATION ${INSTALL_SUBMODULES_RUN}
        ARCHIVE  DESTINATION ${INSTALL_SUBMODULES_ARC}
        LIBRARY  DESTINATION ${INSTALL_SUBMODULES_LIB}
        INCLUDES DESTINATION ${INSTALL_SUBMODULES_INC}
)

# export project
#install(EXPORT appbricks_targets
#        FILE appbricksTargets.cmake
#        NAMESPACE apb::
#        DESTINATION ${INSTALL_CONFIGDIR}
#)

add_subdirectory(unit_tests EXCLUDE_FROM_ALL)

# run tests
enable_testing()
add_test(NAME tests_run
    COMMAND tests
)