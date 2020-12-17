# Copyright (C) 2020 by Sandy McNeil <g7mzrdev@gmail.com>

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License or (at your option) version 3 or any later version
# accepted by the membership of KDE e.V. (or its successor approved
# by the membership of KDE e.V.), which shall act as a proxy 
# defined in Section 14 of version 3 of the license.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
