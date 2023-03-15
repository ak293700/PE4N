find_path(SDL2_INCLUDE_DIR SDL.h PATHS ${SDL2_INCLUDE_DIRS})
find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${SDL2_LIBRARIES})

if(SDL2_INCLUDE_DIR AND SDL2_LIBRARY)
    set(SDL2_FOUND TRUE)
endif()

if(SDL2_FOUND)
    if(NOT SDL2_FIND_QUIETLY)
        message(STATUS "Found SDL2: ${SDL2_LIBRARY}")
    endif()
else()
    if(SDL2_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find SDL2 library")
    endif()
endif()

set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
set(SDL2_LIBRARIES ${SDL2_LIBRARY})
