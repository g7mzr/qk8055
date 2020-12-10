# Top Level CMakeList.txt

cmake_minimum_required(VERSION 3.0)

project(
    qk8055   
    VERSION 0.1.0 
    DESCRIPTION "Qt Demonstration Program for Velleman K8055 Board"
)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)


# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Find the QT5 Linguist Tools
find_package(Qt5LinguistTools)

include(cmake/modules.cmake)
include(cmake/includes.cmake)
include(cmake/copyright.cmake)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in" 
    "${PROJECT_SOURCE_DIR}/config.h"
)

add_subdirectory(src)
