cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
  SLEFE
  VERSION 1.0
  DESCRIPTION "A library to build subdividable linear efficient function enclosures"
  LANGUAGES CXX)

message (STATUS "CMAKE_CURRENT_SOURCE_DIR is ${CMAKE_CURRENT_SOURCE_DIR}")

if (NOT CMAKE_BUILD_TYPE)
  message (STATUS "Setting build type to 'Release' as none was specified")
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message (STATUS "Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

# enable folders for projects in Visual Studio
if (CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # ensure -std=c++xx instead of -std=g++xx
  set (CMAKE_CXX_EXTENSIONS OFF)

  # support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # indicate documentation build as an option and set it to ON by default
  # option(BUILD_DOC "Build documentation" ON)

  # docs only available if this is the main app
  # find_package(Doxygen QUIET)
  # if (Doxygen_FOUND)
  #  add_subdirectory(doc)
  #  install(CODE  "EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target doc)")
  #  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/doc)
  #  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/latex DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/doc)
  # else()
  #  message (STATUS "Doxygen not found, not building docs")
  # endif()
endif()

# add directory of library source files
add_subdirectory(src/lib)

# add directory of library demo application
add_subdirectory(src/app)

# add directory of library unit tests
add_subdirectory(src/tst)


