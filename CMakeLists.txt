cmake_minimum_required(VERSION 3.16)
project(cs-study CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

include(CTest)
enable_testing()

# --- GoogleTest, fetched at configure time ---------------------------------
include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

# --- Auto-discover src/cpp/NN-topic modules --------------------------------
#
# No per-module CMakeLists.txt needed. Drop files into src/cpp/NN-topic/ and
# they're picked up next time this file is configured:
#
#   - any *.cpp file that isn't a test file goes into a static library named
#     after the module directory (e.g. `02-arrays`), header-only modules just
#     get their directory added to the include path
#   - any *_test.cpp / *_tests.cpp file becomes part of a GoogleTest
#     executable named `<module>_test`, linked against that library (if any)
#     plus gtest_main, and registered with ctest
#
file(GLOB module_dirs RELATIVE ${CMAKE_SOURCE_DIR}/src/cpp CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/src/cpp/*)

foreach(module_dir ${module_dirs})
  set(module_path ${CMAKE_SOURCE_DIR}/src/cpp/${module_dir})
  if(NOT IS_DIRECTORY ${module_path})
    continue()
  endif()

  file(GLOB test_sources CONFIGURE_DEPENDS
       ${module_path}/*_test.cpp ${module_path}/*_tests.cpp)
  file(GLOB impl_sources CONFIGURE_DEPENDS ${module_path}/*.cpp)
  if(test_sources)
    list(REMOVE_ITEM impl_sources ${test_sources})
  endif()

  set(has_impl_lib FALSE)
  if(impl_sources)
    add_library(${module_dir} STATIC ${impl_sources})
    target_include_directories(${module_dir} PUBLIC ${module_path})
    set(has_impl_lib TRUE)
  endif()

  if(test_sources)
    set(test_target ${module_dir}_test)
    add_executable(${test_target} ${test_sources})
    target_include_directories(${test_target} PRIVATE ${module_path})
    if(has_impl_lib)
      target_link_libraries(${test_target} PRIVATE ${module_dir})
    endif()
    target_link_libraries(${test_target} PRIVATE gtest_main)
    add_test(NAME ${test_target} COMMAND ${test_target})
  endif()
endforeach()
