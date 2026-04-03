cmake_minimum_required(VERSION 3.16)

project(data_structures_docker C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(ENABLE_ASAN     "Enable AddressSanitizer + UBSan" OFF)
option(ENABLE_VALGRIND "Build optimised for Valgrind (no sanitisers)" OFF)

if(ENABLE_ASAN AND ENABLE_VALGRIND)
  message(FATAL_ERROR "ENABLE_ASAN and ENABLE_VALGRIND are mutually exclusive.")
endif()

if(ENABLE_VALGRIND)
  message(STATUS "Valgrind mode: sanitisers disabled, -g -O0 expected from preset.")
endif()

file(
  GLOB_RECURSE DATA_STRUCTURES_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/Data-Structures/*.c"
)

if(NOT DATA_STRUCTURES_SOURCES)
  message(FATAL_ERROR "No C source files were found under Data-Structures.")
endif()

foreach(source_file IN LISTS DATA_STRUCTURES_SOURCES)
  file(
    RELATIVE_PATH relative_source
    "${CMAKE_CURRENT_SOURCE_DIR}/Data-Structures"
    "${source_file}"
  )

  string(REGEX REPLACE "\\.[^.]+$" "" target_name "${relative_source}")
  string(REGEX REPLACE "[^A-Za-z0-9_]" "_" target_name "${target_name}")

  add_executable("${target_name}" "${source_file}")
  target_compile_options("${target_name}" PRIVATE
    -Wall -Wextra -Wpedantic
    -Wshadow
    -Wformat=2
    -Wnull-dereference
    -Wstrict-prototypes
    -Wmissing-prototypes
    -Wpointer-arith
    -Wcast-align
    -Wwrite-strings
    -Wundef
  )
  if(ENABLE_ASAN)
    target_compile_options("${target_name}" PRIVATE
      -fsanitize=address,undefined
      -fno-omit-frame-pointer
      -fno-optimize-sibling-calls
    )
    target_link_options("${target_name}" PRIVATE
      -fsanitize=address,undefined
    )
  endif()
  set_target_properties(
    "${target_name}"
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endforeach()
