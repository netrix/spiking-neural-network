cmake_minimum_required(VERSION 2.8)
project(snn)

# Tests
option(BUILD_UNITTESTS "Build Unit tests" 0)

#if(${BUILD_UNITTESTS})
#	add_subdirectory(modules/gtest)
#	include_directories(modules/gtest/include)
#endif()

# Submodules
add_subdirectory(modules/nlib)

# Project files
include_directories(modules/nlib/src/)
add_subdirectory(src)
