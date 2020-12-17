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
# Configuration Checks

if (CMAKE_SYSTEM_PROCESSOR EQUAL "x86_64")
    SET(SYSTEM_LIBRARY "/usr/lib64")
else()
    SET(SYSTEM_LIBRARY "/usr/lib")
endif()


# check if k8055.h exists
CHECK_INCLUDE_FILE(k8055.h K8055_H_EXISTS)
if(NOT K8055_H_EXISTS)
    Message(FATAL_ERROR "*** ERROR *** libk8055 header file (k8055.h) not found") 
endif() 
    
# Check if libk8055 exists
Check_Library_Exists(libk8055.so OpenDevice ${SYSTEM_LIBRARY} LIBK8055_FOUND)
if(NOT LIBK8055_FOUND)
    Message(FATAL_ERROR "*** ERROR *** libk8055.so not found") 
endif()
 
