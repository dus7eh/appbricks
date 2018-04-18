cmake_minimum_required(VERSION 3.0)
project(textbrick)
add_library(textbrick
    text.cpp
    textutils.cpp
)

target_include_directories(textbrick PRIVATE ../include)
target_compile_features(textbrick PRIVATE cxx_lambda_init_captures)