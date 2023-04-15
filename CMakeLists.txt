cmake_minimum_required(VERSION 3.16)

project("LUtils" CXX C)

option(LMATH_USE_SHORTCUT_TYPES "Use lmath vector types without the namespace" OFF)

file(GLOB SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lutils/*.cpp lmath/*.cpp)
file(GLOB HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lutils/*.h lmath/*.h)

add_library(LUtils ${SRC_FILES} ${HEADER_FILES})

target_include_directories(LUtils PUBLIC .)

set_property(TARGET LUtils PROPERTY CXX_STANDARD 17)
set_property(TARGET LUtils PROPERTY CXX_STANDARD_REQUIRED ON)

if(LMATH_USE_SHORTCUT_TYPES)
	target_compile_definitions(LUtils PUBLIC LMATH_USE_SHORTCUT_TYPES=1)
endif()
