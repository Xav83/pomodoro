cmake_minimum_required(VERSION 3.18)

project(Project)

add_executable(pomodoro src/main.cpp)
set_property(TARGET pomodoro PROPERTY CXX_STANDARD 17)
