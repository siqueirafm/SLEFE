set (APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

set (SLEFE_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/hpp)

file (GLOB CPP_FILES ${APP_SRC}/*.cpp)

add_executable(slefe-app "")

target_compile_features(slefe-app PRIVATE cxx_std_17)

if (MSVC)
  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(slefe-app PRIVATE /W4 /WX- /O2 /MD)
  else ()
    target_compile_options(slefe-app PRIVATE /W4 /WX- /MDd)
  endif ()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(slefe-app PRIVATE -Wall -Wextra -Werror -pedantic -O3)
  else ()
    target_compile_options(slefe-app PRIVATE -Wall -Wextra -Werror -pedantic)
  endif ()
endif ()

target_sources(slefe-app PRIVATE ${CPP_FILES})

target_include_directories(
  slefe-app
    PRIVATE
       ${SLEFE_INC}
)

target_link_libraries(
  slefe-app
    PRIVATE
      slefe
)

install(TARGETS slefe-app DESTINATION bin)
