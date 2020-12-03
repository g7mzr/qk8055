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
 
