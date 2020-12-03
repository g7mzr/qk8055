# src directory CMakeList.txt

include_directories("${PROJECT_SOURCE_DIR}")

set(qk8055_SRC
  main.cpp
  qk8055.cpp
  k8055_guiview.cpp
)

# Tell CMake to create the helloworld executable
add_executable(qk8055 ${qk8055_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(qk8055 
    Qt5::Widgets 
    libk8055.so
)

# Install the executable
install(TARGETS qk8055 DESTINATION bin)
