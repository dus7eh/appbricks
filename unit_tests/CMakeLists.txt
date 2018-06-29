cmake_minimum_required(VERSION 3.0)
# project configuration
project(tests VERSION 0.1 LANGUAGES CXX)

include(../scripts/DownloadGoogleTest.cmake)

add_executable(tests
    src/test_text.cpp
    src/test_blob.cpp
    src/test_stringview.cpp
    src/test_optional.cpp
)

option(DEV_MODE "Compile and link against the code sources instead of install path" OFF)

if (DEV_MODE)
    target_include_directories(tests PRIVATE
                        ${CMAKE_BINARY_DIR}/code)
else()
    target_include_directories(tests PRIVATE ${CMAKE_BINARY_DIR}/include)
endif()

target_link_libraries(tests gtest_main textbrick corebrick)

# install
include(../scripts/InstallDirHelpers.cmake)
install(TARGETS  tests
        RUNTIME  DESTINATION ${INSTALL_SUBMODULES_RUN}
        ARCHIVE  DESTINATION ${INSTALL_SUBMODULES_ARC}
        LIBRARY  DESTINATION ${INSTALL_SUBMODULES_LIB}
)