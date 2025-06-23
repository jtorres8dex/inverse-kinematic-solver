
cmake_minimum_required(VERSION 3.16)
project(IKSolver)

set(CMAKE_CXX_STANDARD 17)

# Automatically gather all .cpp files from the src directory
file(GLOB SOURCES "core/src/*.cpp")

# Create the executable using the gathered sources
add_executable(ik_solver ${SOURCES})

# Include directories
target_include_directories(ik_solver PRIVATE core/inc)

# Link libraries (Eigen in this case)
find_package(Eigen3 REQUIRED)
target_link_libraries(ik_solver PRIVATE Eigen3::Eigen)

