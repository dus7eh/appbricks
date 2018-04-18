cmake_minimum_required(VERSION 3.0)
project(appbricks)
add_library(appbricks
    src/main.cpp  
)

#add_subdirectory(ext/googletest-release-1.8.0)
add_subdirectory(src/text)

target_include_directories(appbricks PRIVATE include)