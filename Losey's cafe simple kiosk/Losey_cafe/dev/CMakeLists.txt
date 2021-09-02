cmake_minimum_required(VERSION 3.10)

PROJECT(Losey)

set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
include_directories ( inc )

set ( manager_src
    inc/common.h
    src/Manager.cpp
)

set ( client_src
    inc/common.h
    src/Client.cpp
)

add_executable ( manager ${manager_src} )
add_executable ( client ${client_src} )

install ( TARGETS manager client
    RUNTIME DESTINATION bin
)
