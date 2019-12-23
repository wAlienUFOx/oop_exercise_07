cmake_minimum_required (VERSION 3.5)

project(lab7)

add_executable(oop_exercise_07
  main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g3 -Wextra")

set_target_properties(oop_exercise_07 PROPERTIES CXX_STANDART 14 CXX_STANDART_REQUIRED ON)
