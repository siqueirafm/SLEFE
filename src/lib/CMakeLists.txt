set (SLEFELIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/hpp)
set (SLEFELIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

file (GLOB HPP_FILES ${SLEFELIB_INC}/*.hpp)
file (GLOB CPP_FILES ${SLEFELIB_SRC}/*.cpp)

# Make a static library (omit STATIC if you want user setting to decide)
add_library(slefe
  STATIC
    ${HPP_FILES}
    ${CPP_FILES}
  )

# Library need these directories, and its users will need them too.
target_include_directories(slefe
  PUBLIC 
    $<INSTALL_INTERFACE:include>
    ${SLEFELIB_INC}
)

# All users of this library will need to have at list C++ 17
target_compile_features(slefe PUBLIC cxx_std_17)

# Set compiler options for MS Visual Studio and everything else
if (MSVC)
  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(slefe PRIVATE /W4 /WX- /O2 /MD)
  else ()
    target_compile_options(slefe PRIVATE /W4 /WX- /MDd)
  endif ()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  list (APPEND flags )
  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(slefe PRIVATE -Wall -Wextra -Werror -pedantic -O3)
  else ()
    target_compile_options(slefe PRIVATE -Wall -Wextra -Werror -pedantic)
  endif ()
endif ()

source_group(
  TREE "${SLEFELIB_INC}"
  PREFIX "Header Files"
  FILES ${HPP_FILES})

source_group(
  TREE "${SLEFELIB_SRC}"
  PREFIX "Source Files"
  FILES ${CPP_FILES})

install(TARGETS slefe DESTINATION lib)
install(FILES ${HPP_FILES} DESTINATION include)
