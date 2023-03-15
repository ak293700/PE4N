cmake_minimum_required(VERSION 3.21)
project(PE4N)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SDL2_INCLUDE_DIRS /opt/homebrew/include/SDL2)
set(SDL2_LIBRARIES /opt/homebrew/lib/libSDL2.dylib)
set(SDL2_TTF_LIBRARIES /opt/homebrew/lib/libSDL2_ttf.dylib)


# Find every source file
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")
add_executable(PE4N ${SRC_FILES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

