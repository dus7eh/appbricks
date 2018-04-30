cmake_minimum_required(VERSION 3.0)

# project configuration
project(textbrick VERSION 0.1 LANGUAGES CXX)
add_library(textbrick
    text.cpp
    textutils.cpp
)

target_include_directories(textbrick INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(textbrick PROPERTIES PUBLIC_HEADER
    "text.h;textutils.h"
)

install(TARGETS  textbrick
        RUNTIME  DESTINATION ${INSTALL_SUBMODULES_RUN}
        ARCHIVE  DESTINATION ${INSTALL_SUBMODULES_ARC}
        LIBRARY  DESTINATION ${INSTALL_SUBMODULES_LIB}
        INCLUDES DESTINATION ${INSTALL_SUBMODULES_INC}
        PUBLIC_HEADER DESTINATION ${INSTALL_SUBMODULES_INC}/text/
)