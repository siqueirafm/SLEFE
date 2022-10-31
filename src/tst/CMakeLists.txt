set (TST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

set (SLEFE_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/hpp)

file (GLOB CPP_FILES ${TST_SRC}/*.cpp)

option (BUILD_UNIT_TESTS "Build unit tests" OFF)
message (STATUS "Build unit tests: ${BUILD_UNIT_TESTS}")

if (BUILD_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
  )

  if (NOT googletest_POPULATED)

    FetchContent_Populate(googletest)

    # Prevent GoogleTest from overriding our compiler/linker options with building with Visual Studio
    set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Prevent GoogleTest from using PThreads
    set (gtest_disable_pthreads ON CACHE BOOL "" FORCE)

    # Where Google Test header files can be found.
    set(GTEST_BUILD_INCLUDE_DIRS
      "${gtest_SOURCE_DIR}/include"
      "${gtest_SOURCE_DIR}"
    )

    message (STATUS "googletest_SOURCE_DIR is ${googletest_SOURCE_DIR}")
    message (STATUS "googletest_BINARY_DIR is ${googletest_BINARY_DIR}")

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    # Silence std::tr1 warning on MSVC
    if (MSVC)
      foreach (_tgt gtest gtest_main gmock gmock_main)
        target_compile_definitions(${_tgt}
	  PRIVATE
	    "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
	)
      endforeach()
    endif()

  endif()

  add_executable(slefe-tst "")

  target_compile_features(slefe-tst PRIVATE cxx_std_17)

  if (MSVC)
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(slefe-tst PRIVATE /W4 /WX- /O2 /MD)
    else ()
      target_compile_options(slefe-tst PRIVATE /W4 /WX- /MDd)
    endif ()
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(slefe-tst PRIVATE -Wall -Wextra -Werror -pedantic -O3)
    else ()
      target_compile_options(slefe-tst PRIVATE -Wall -Wextra -Werror -pedantic)
    endif ()
  endif ()  

  target_sources(slefe-tst PRIVATE ${CPP_FILES})

  target_include_directories(
    slefe-tst
      PRIVATE
        ${SLEFE_INC}
  )

  target_link_libraries(
    slefe-tst
      PRIVATE
      slefe
      gtest_main
  )

  enable_testing()

  add_test(
    NAME google_test
    COMMAND $<TARGET_FILE:slefe-tst>
  )

  install(TARGETS slefe-tst DESTINATION tst)

 endif()
