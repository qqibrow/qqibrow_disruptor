cmake_minimum_required(VERSION 2.8)
#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -stdlib=libc++")

#INCLUDE_DIRECTORIES(~/boost_1_56_0)
INCLUDE_DIRECTORIES(../include)
AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_library(${library_name} SHARED ${SRC_LIST})

