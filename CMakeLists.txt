cmake_minimum_required(VERSION 3.17)

project(Project)

include(${PROJECT_SOURCE_DIR}/.cmake/cppcheck.cmake)
include(${PROJECT_SOURCE_DIR}/.cmake/clang_tidy.cmake)

find_program(
  CONAN_EXE
  NAMES conan conan.exe
  HINTS "C:/Program Files/Conan/conan/" "/home/vsts/.local/bin"
  DOC "Conan executable" REQUIRED)

if(APPLE)
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/apple)
  set(POMODORO_RESOURCES_INSTALL_FOLDER
      "~/Library/Application Support/Pomodoro")
elseif(UNIX)
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/linux)
  set(POMODORO_RESOURCES_INSTALL_FOLDER "~/.pomodoro")
else()
  set(POMODORO_PROFILE ${PROJECT_SOURCE_DIR}/.conan/profiles/windows)
  set(POMODORO_RESOURCES_INSTALL_FOLDER "C:/ProgramData/pomodoro")
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

# Pomodoro shared library

add_library(
  pomodoro_lib
  src/shared/Timers.cpp src/shared/Configuration.cpp
  src/shared/ConfigurationFile.cpp src/shared/Pomodoro.cpp src/shared/Timer.cpp
  src/shared/utility/FilesDictionary.cpp)
set_property(TARGET pomodoro_lib PROPERTY CXX_STANDARD 17)
target_compile_options(
  pomodoro_lib
  PRIVATE $<$<CXX_COMPILER_ID:GNU>: -fprofile-arcs -ftest-coverage>
          $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
target_link_libraries(
  pomodoro_lib PUBLIC CONAN_PKG::fmt CONAN_PKG::nlohmann_json CONAN_PKG::gtest
                      $<$<CXX_COMPILER_ID:GNU>: -fprofile-arcs -ftest-coverage>)
target_include_directories(pomodoro_lib PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Pomodoro command line application

add_executable(pomodoro src/command_line/main.cpp
                        src/command_line/CommandLineParser.cpp)
set_property(TARGET pomodoro PROPERTY CXX_STANDARD 17)
target_compile_options(
  pomodoro PRIVATE $<$<CXX_COMPILER_ID:GNU>: -fprofile-arcs -ftest-coverage>
                   $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
target_link_libraries(pomodoro PUBLIC pomodoro_lib CONAN_PKG::sfml
                                      CONAN_PKG::argh)
target_include_directories(pomodoro PUBLIC src)

make_directory("${POMODORO_RESOURCES_INSTALL_FOLDER}")

add_custom_command(
  TARGET pomodoro
  POST_BUILD
  COMMAND cp *.ogg ${POMODORO_RESOURCES_INSTALL_FOLDER}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res/
  COMMENT "Moves the sound files into the right folder")

# Pomodoro desktop application

add_executable(pomodoro_desktop src/desktop/main.cpp src/desktop/Fonts.cpp)
set_property(TARGET pomodoro_desktop PROPERTY CXX_STANDARD 17)
target_compile_options(
  pomodoro_desktop
  PRIVATE $<$<CXX_COMPILER_ID:GNU>: -fprofile-arcs -ftest-coverage>
          $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
target_link_libraries(pomodoro_desktop PUBLIC pomodoro_lib CONAN_PKG::sfml)
target_include_directories(pomodoro_desktop PUBLIC src)

make_directory("${POMODORO_RESOURCES_INSTALL_FOLDER}/Fonts")

add_custom_command(
  TARGET pomodoro_desktop
  POST_BUILD
  COMMAND cp -rf Fonts ${POMODORO_RESOURCES_INSTALL_FOLDER}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res/
  COMMENT "Moves the sound files into the right folder")

# Pomodoro tests

include(CTest)

file(GLOB POMODORO_TEST_FILES ${PROJECT_SOURCE_DIR}/tst/*.cpp)

add_executable(pomodoro_tests ${POMODORO_TEST_FILES})
set_property(TARGET pomodoro_tests PROPERTY CXX_STANDARD 17)
target_compile_options(
  pomodoro_tests
  PRIVATE $<$<CXX_COMPILER_ID:GNU>: -fprofile-arcs -ftest-coverage>
          $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
target_link_libraries(pomodoro_tests PUBLIC pomodoro_lib)
target_include_directories(pomodoro_tests PUBLIC src/shared)

include(GoogleTest)
gtest_discover_tests(pomodoro_tests)
