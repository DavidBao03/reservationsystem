cmake_minimum_required(VERSION 3.24)
project(reservationSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(reservationSystem reservationSystem.cpp indentity.cpp manager.cpp student.cpp teacher.cpp)
