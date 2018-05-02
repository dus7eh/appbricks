cmake_minimum_required(VERSION 3.0)

# project configuration
project(appbricks VERSION 0.1 LANGUAGES CXX)
add_library(appbricks
    src/main.cpp
)
# set installation related variables
set(INSTALL_SUBMODULES_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Installation base directory")
include(InstallDirHelpers.cmake)

# submodules settings
add_subdirectory(src/text)
add_subdirectory(src/core)

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

# section for gtest and unit_test build
add_subdirectory(unit_tests)
add_custom_target(tests_run ALL
    COMMAND unit_tests/tests.exe
    COMMENT "Running tests"
    DEPENDS tests)