cmake_minimum_required(VERSION 2.8)

INCLUDE_DIRECTORIES(~/boost_1_56_0)
INCLUDE_DIRECTORIES(../include)
AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_library(${library_name} SHARED ${SRC_LIST})

