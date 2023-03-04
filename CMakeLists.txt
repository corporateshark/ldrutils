cmake_minimum_required(VERSION 3.16)

project("LUtils" CXX C)

file(GLOB SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lutils/*.cpp)
file(GLOB HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lutils/*.h)

add_library(LUtils ${SRC_FILES} ${HEADER_FILES})

target_include_directories(LUtils PUBLIC .)
