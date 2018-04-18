cmake_minimum_required(VERSION 3.0)
project(appbricks)
add_library(appbricks
    src/main.cpp  
)

add_subdirectory(src/text)
target_link_libraries(textbrick)
target_include_directories(appbricks PRIVATE src)
install(TARGETS appbricks
        DESTINATION bin
)