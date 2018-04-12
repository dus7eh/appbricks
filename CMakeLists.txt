cmake_minimum_required(VERSION 3.0)
project(appbricks)
add_library(appbricks
    src/main.cpp
    src/text/text.cpp
    src/text/textutils.cpp   
)

add_subdirectory(ext/googletest-release-1.8.0)

target_include_directories(appbricks PRIVATE src)
target_compile_features(appbricks PRIVATE cxx_lambda_init_captures)