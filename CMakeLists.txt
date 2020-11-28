cmake_minimum_required(VERSION 3.18)

project(Project)

find_program(
  CONAN_EXE
  NAMES conan conan.exe
  HINTS "C:/Program Files/Conan/conan/"
  DOC "Conan executable" REQUIRED)

execute_process(
    COMMAND ${CONAN_EXE} remote add url "https://api.bintray.com/conan/bincrafters/public-conan"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
execute_process(
    COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing -pr=.conan/profiles/windows -s build_type=Debug
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
execute_process(
    COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing -pr=.conan/profiles/windows -s build_type=Release
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

include(${PROJECT_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_executable(pomodoro src/main.cpp src/Timers.cpp src/Pomodoro.cpp src/Timer.cpp)
set_property(TARGET pomodoro PROPERTY CXX_STANDARD 17)
target_link_libraries(pomodoro PUBLIC CONAN_PKG::fmt CONAN_PKG::sfml)

make_directory("C:/ProgramData/pomodoro")

add_custom_command(TARGET pomodoro POST_BUILD
                    COMMAND cp * "C:/ProgramData/pomodoro"
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res/
                   COMMENT "Moves the sound files into the right folder")
