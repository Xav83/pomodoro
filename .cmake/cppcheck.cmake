set(RUN_CPPCHECK
    OFF
    CACHE
      BOOL
      "Sets to ON if you want to run cppcheck when compiling Noisy. OFF by default"
)

if(NOT RUN_CPPCHECK)
  message(STATUS "Cppcheck deactivated during compilation.")
else()
  message(STATUS "Cppcheck activated during compilation.")
  if(NOT
     (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles"
      OR ${CMAKE_GENERATOR} STREQUAL "Ninja"
      OR ${CMAKE_GENERATOR} MATCHES "Visual Studio*"))
    message(
      FATAL_ERROR
        "Cppcheck is not supported with the Generator ${CMAKE_GENERATOR}. The only generators supported are \"Ninja\", \"Visual Studio\" and \"Unix Makefiles\"."
    )
  endif()

  unset(CPPCHECK CACHE)
  find_program(
    CPPCHECK
    NAMES cppcheck
    HINTS "C:\\Program Files\\Cppcheck")

  if(NOT CPPCHECK)
    message(
      FATAL_ERROR
        "Cppcheck not found. You can install it using Chocolatey on Windows (https://chocolatey.org/packages/cppcheck)."
    )
  endif()

  function(cppcheck_version output_var)
    # Runs the command to get the cppcheck version
    execute_process(COMMAND ${CPPCHECK} --version
                    OUTPUT_VARIABLE CPPCHECK_VERSION_RAW_OUTPUT)

    # Extracts the version from the output of the command run before
    string(SUBSTRING ${CPPCHECK_VERSION_RAW_OUTPUT} 9 -1
                     CPPCHECK_VERSION_OUTPUT)
    string(STRIP ${CPPCHECK_VERSION_OUTPUT} CPPCHECK_VERSION_OUTPUT)

    set(${output_var}
        ${CPPCHECK_VERSION_OUTPUT}
        PARENT_SCOPE)
  endfunction()

  cppcheck_version(CPPCHECK_VERSION_OUTPUT)

  message(STATUS "Cppcheck version detected : ${CPPCHECK_VERSION_OUTPUT}")

  set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")

  set(CPPCHECK_SUPPRESSION_FILE
      "${PROJECT_SOURCE_DIR}/.cppcheck/suppression.txt")

  if(NOT EXISTS ${CPPCHECK_SUPPRESSION_FILE})
    message(
      FATAL_ERROR
        "Cppcheck - Missing suppression list file: ${CPPCHECK_SUPPRESSION_FILE} not found."
    )
  endif()

  if(${CMAKE_GENERATOR} STREQUAL "Unix Makefiles" OR ${CMAKE_GENERATOR}
                                                     STREQUAL "Ninja")
    list(
      APPEND
      CMAKE_CXX_CPPCHECK
      "--enable=warning,style,performance,portability"
      "--inconclusive"
      "--error-exitcode=1"
      "--std=c++14"
      "--force"
      "--inline-suppr"
      "--suppressions-list=${CPPCHECK_SUPPRESSION_FILE}")
    message(STATUS "Command Cppcheck: ${CMAKE_CXX_CPPCHECK}")
  else()
    add_custom_target(
      CPPCHECK_ANALYSIS ALL
      COMMAND ${CMAKE_CXX_CPPCHECK} --project=${CMAKE_PROJECT_NAME}.sln
              --suppressions-list=${CPPCHECK_SUPPRESSION_FILE}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Static code analysis using cppcheck.")
  endif()
endif()
