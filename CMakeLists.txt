cmake_minimum_required(VERSION 3.17)

project(Project)

find_program(
  CONAN_EXE
  NAMES conan conan.exe
  HINTS "C:/Program Files/Conan/conan/" "/home/vsts/.local/bin"
  DOC "Conan executable" REQUIRED)

if(APPLE)
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/apple)
  set(POMODORO_SOUND_INSTALL_FOLDER "~/Library/Application Support/Pomodoro")
elseif(UNIX)
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/linux)
  set(POMODORO_SOUND_INSTALL_FOLDER "~/.pomodoro")
else()
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/windows)
  set(POMODORO_SOUND_INSTALL_FOLDER "C:/ProgramData/pomodoro")
endif()

execute_process(
  COMMAND ${CONAN_EXE} remote add url
          "https://api.bintray.com/conan/bincrafters/public-conan"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

execute_process(
  COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing
          -pr=${POMODORO_PROFILE} -s build_type=Debug
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
execute_process(
  COMMAND ${CONAN_EXE} install . --install-folder=build --build=missing
          -pr=${POMODORO_PROFILE} -s build_type=Release
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

include(${PROJECT_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_executable(pomodoro src/main.cpp src/Timers.cpp src/Pomodoro.cpp
                        src/Timer.cpp src/utility/SoundsDictionary.cpp)
set_property(TARGET pomodoro PROPERTY CXX_STANDARD 17)
target_link_libraries(pomodoro PUBLIC CONAN_PKG::argh CONAN_PKG::fmt
                                      CONAN_PKG::sfml)

make_directory("${POMODORO_SOUND_INSTALL_FOLDER}")

add_custom_command(
  TARGET pomodoro
  POST_BUILD
  COMMAND cp *.ogg ${POMODORO_SOUND_INSTALL_FOLDER}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res/
  COMMENT "Moves the sound files into the right folder")
