cmake_minimum_required(VERSION 3.14)
project(NtParser)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "-g  -ggdb -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

include_directories(gen)
include_directories(include)

set(GENERATED_SOURCES gen/scanner.c gen/parser.tab.c)

add_library(ntparser ${GENERATED_SOURCES} src/nt_parser.cpp src/istream_c.cpp)

add_executable(split_nt src/split_nt.cpp)
add_executable(example src/example.cpp)
target_link_libraries(split_nt ntparser)
target_link_libraries(example ntparser)
