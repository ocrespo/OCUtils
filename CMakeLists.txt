cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Force C++14
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

project(OCUtils)

enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra") #-Werror
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
     if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    	set(compilation "-g -O0 ${compilation}")
    else()
    	set(compilation "-O2 ${compilation}")
    endif()
endif()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings} ${compilation}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${compilation}")

  
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set (PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


add_subdirectory(${PROJECT_SOURCE_DIR})



set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")




