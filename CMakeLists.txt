cmake_minimum_required(VERSION 3.10)
project(IKSolver)

set(CMAKE_CXX_STANDARD 17)

# Locate Eigen
find_path(EIGEN3_INCLUDE_DIR Eigen/Dense
  PATHS /usr/local/include /opt/homebrew/include /opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3
)

if (EIGEN3_INCLUDE_DIR)
    message(STATUS "Found Eigen at ${EIGEN3_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Eigen not found. Please check your installation.")
endif()

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/core/inc ${EIGEN3_INCLUDE_DIR})

add_executable(ik_solver core/src/main.cpp core/src/joint.cpp)