cmake_minimum_required(VERSION 3.0)

# project configuration
project(textbrick)
add_library(textbrick
    text.cpp
    textutils.cpp
)

#target_include_directories(textbrick PRIVATE ../include)
set_target_properties(textbrick PROPERTIES PUBLIC_HEADER
    "text.h;textutils.h"
)

#include(${CMAKE_CURRENT_LIST_DIR}/../SubmoduleInstallHelpers.cmake)

install(TARGETS  textbrick
        RUNTIME  DESTINATION ${INSTALL_SUBMODULES_RUN}
        ARCHIVE  DESTINATION ${INSTALL_SUBMODULES_ARC}
        LIBRARY  DESTINATION ${INSTALL_SUBMODULES_LIB}
        INCLUDES DESTINATION ${INSTALL_SUBMODULES_INC}
        PUBLIC_HEADER DESTINATION ${INSTALL_SUBMODULES_INC}/text/
)