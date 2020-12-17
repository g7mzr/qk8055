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

# src directory CMakeList.txt

include_directories("${PROJECT_SOURCE_DIR}")

# Set the qk8055 source variable
set(qk8055_SRC
    main.cpp
    qk8055.cpp
    k8055_guiview.cpp
    gui_debug.cpp
)

# Set the Translation Source files
set(qk8055_TRANSLATION_SRC
    main.cpp
    qk8055.cpp
    k8055_guiview.cpp
    gui_debug.cpp
    k8055_guiview.ui
    qk8055.ui
)

# Set the Translation Files
set(qk8055_TRANSLATION_FILES
    "${PROJECT_SOURCE_DIR}/translations/qk8055_en.ts"
    "${PROJECT_SOURCE_DIR}/translations/qk8055_fr.ts"
)

# create the translation files
qt5_create_translation(QM_FILES ${qk8055_TRANSLATION_SRC} ${qk8055_TRANSLATION_FILES})

# Copy and add the Translation Resource File
configure_file("${PROJECT_SOURCE_DIR}/translations/translations.qrc" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
qt5_add_resources(qk8055_SRC ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc)


# Tell CMake to create the helloworld executable
add_executable(qk8055 
    ${qk8055_SRC}
    ${QM_FILES}        
)


# Use the Widgets module from Qt 5.
target_link_libraries(qk8055 
    Qt5::Widgets 
    libk8055.so
)

# Install the executable
install(TARGETS qk8055 DESTINATION bin)
