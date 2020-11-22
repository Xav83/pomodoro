cmake_minimum_required(VERSION 3.18)

project(Project)

find_program(
  CONAN_EXE
  NAMES conan conan.exe
  DOC "Conan executable" REQUIRED)

execute_process(
    COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing -pr=.conan/profiles/windows -s build_type=Debug
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  execute_process(
    COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing -pr=.conan/profiles/windows -s build_type=Release
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_executable(pomodoro src/main.cpp src/Timers.cpp src/Timer.cpp)
set_property(TARGET pomodoro PROPERTY CXX_STANDARD 17)
target_link_libraries(pomodoro PUBLIC CONAN_PKG::fmt)
