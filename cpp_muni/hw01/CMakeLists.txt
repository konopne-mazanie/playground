cmake_minimum_required(VERSION 3.1)
project(hw01)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

set(HEADERS room.h course.h reservation.h rsystem.h handler.h)
set(SOURCES rsystem.cpp handler.cpp)
add_executable(hw01_main main.cpp ${HEADERS} ${SOURCES})

file(GLOB TEST_SOURCES test*.cpp)
add_executable(hw01_tests ${TEST_SOURCES} ${SOURCES})
