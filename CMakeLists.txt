cmake_minimum_required(VERSION 2.8)
project(snn)

#if(${BUILD_UNITTESTS})
#	add_subdirectory(modules/gtest)
#	include_directories(modules/gtest/include)
#endif()

# Compiling submodules
add_subdirectory("modules/nlib")
add_subdirectory("modules/box2d/Box2D")

# NLib
include_directories("modules/nlib/src/")

# Box2D
include_directories("modules/box2d/Box2D")

# SDL
include("modules/sdl/cmake/sdl.cmake")
link_libraries(${SDL_LIBRARIES})
file(COPY "${SDL_LIBRARIES_PATH}/${SDL_DLL_LIBRARY}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/")
file(COPY "${SDL_LIBRARIES_PATH}/${SDL_IMAGE_DLL_LIBRARY}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/")
file(COPY "${SDL_LIBRARIES_PATH}/${SDL_PNG_DLL_LIBRARY}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/")

add_subdirectory(src)
