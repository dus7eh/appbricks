cmake_minimum_required(VERSION 3.0)

# project configuration
project(corebrick VERSION 0.1 LANGUAGES CXX)
add_library(corebrick INTERFACE)

target_compile_definitions(corebrick INTERFACE  LIBRARY_HEADER_ONLY)
target_include_directories(corebrick INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS  corebrick
        RUNTIME  DESTINATION ${INSTALL_SUBMODULES_RUN}
        ARCHIVE  DESTINATION ${INSTALL_SUBMODULES_ARC}
        LIBRARY  DESTINATION ${INSTALL_SUBMODULES_LIB}
        INCLUDES DESTINATION ${INSTALL_SUBMODULES_INC}
        PUBLIC_HEADER DESTINATION ${INSTALL_SUBMODULES_INC}/core/
)

install(FILES "variant.h" DESTINATION ${INSTALL_SUBMODULES_INC})