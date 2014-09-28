cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME Disruptor)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

################################
# Normal Libraries & Executables
################################
set(library_name qqibrow_disruptor)
#set(boost ~/boost_1_56_0/)
add_subdirectory(src)
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere.

################################
# Testing
################################
if (test)
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/gtest-1.6.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  # header files directory and boost directory
  include_directories(./include ${boost})

  ##############
  # Unit Tests
  ##############
  AUX_SOURCE_DIRECTORY(tests TEST_LIST)
  add_executable(runUnitTests ${TEST_LIST})
  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)
  # Extra linking for the project.
  target_link_libraries(runUnitTests ${library_name})
endif()
