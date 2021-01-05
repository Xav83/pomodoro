set(RUN_CLANG_TIDY
    OFF
    CACHE
      BOOL
      "Sets to ON if you want to run cppcheck when compiling Noisy. OFF by default"
)

if(NOT RUN_CLANG_TIDY)
  message(STATUS "Clang-tidy deactivated during compilation.")
else()
  message(STATUS "Clang-tidy activated during compilation.")
  if(NOT (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles" OR ${CMAKE_GENERATOR}
                                                          STREQUAL "Ninja"))
    message(
      FATAL_ERROR
        "Cppcheck is not supported with the Generator ${CMAKE_GENERATOR}. The only generators supported are \"Ninja\" and \"Unix Makefiles\"."
    )
  endif()

  unset(CLANG_TIDY CACHE)
  find_program(
    CLANG_TIDY
    NAMES clang-tidy
    HINTS "C:\\Program Files\\LLVM\\bin")
  if(NOT CLANG_TIDY)
    message(FATAL_ERROR "Clang-tidy not found.")
  endif()

  function(clang_tidy_version output_var)
    # Runs the command to get the cppcheck version
    execute_process(COMMAND ${CLANG_TIDY} --version
                    OUTPUT_VARIABLE CLANG_TIDY_VERSION_RAW_OUTPUT)

    # Extracts the version from the output of the command run before
    string(SUBSTRING ${CLANG_TIDY_VERSION_RAW_OUTPUT} 39 7
                     CLANG_TIDY_VERSION_OUTPUT)
    string(STRIP ${CLANG_TIDY_VERSION_OUTPUT} CLANG_TIDY_VERSION_OUTPUT)

    set(${output_var}
        ${CLANG_TIDY_VERSION_OUTPUT}
        PARENT_SCOPE)
  endfunction()

  clang_tidy_version(CLANG_TIDY_VERSION_OUTPUT)

  message(STATUS "Clang-tidy version detected : ${CLANG_TIDY_VERSION_OUTPUT}")

  set(CMAKE_CXX_CLANG_TIDY
      ${CLANG_TIDY}
      -checks=-*readability-*,modernize-*,portability-*,performance-*
      --warnings-as-errors=*)
endif()
