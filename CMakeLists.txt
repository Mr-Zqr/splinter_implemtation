# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (sample_project)


# Add an executable
add_executable(sample_project main.cpp)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
# Find Eigen
find_package(Eigen3 REQUIRED)

# Include Eigen headers
include_directories(${EIGEN3_INCLUDE_DIR})
# If there are any libraries that need to be linked, use the following command
target_link_libraries(sample_project ${PROJECT_SOURCE_DIR}/x86-64/libsplinter-3-0.so)