﻿project ("palindrome")
cmake_minimum_required (VERSION 3.8)

# Compiler flags
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

# Add sources
set(HEADERS BinTree.h)
set(SOURCES BinTree.cpp)
add_executable (game game.cpp ${HEADERS} ${SOURCES})
