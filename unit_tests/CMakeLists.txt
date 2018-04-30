cmake_minimum_required(VERSION 3.0)

# project configuration
project(tests VERSION 0.1 LANGUAGES CXX)

include(downloadGoogleTest.cmake)

add_executable(tests
    test_text.cpp
    test_variant.cpp
)

# fixme: consider include dir instead src - this would require post installation stage
target_include_directories(tests PRIVATE ${CMAKE_BINARY_DIR}/src)
target_link_libraries(tests gtest_main
    textbrick corebrick)
    
add_custom_command(COMMAND $CMAKE_CURRENT_BINARY_DIR}/tests.exe
    POST_BUILD
    TARGET tests
    COMMENT "Running tests")