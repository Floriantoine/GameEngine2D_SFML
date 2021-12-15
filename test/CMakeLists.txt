cmake_minimum_required(VERSION 3.5)

project("R-type's test" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
        ./src
)

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic
)

set(SRCS
        main.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_test ${SRCS})

target_link_libraries(r-type_test PRIVATE
  Catch2::Catch2WithMain
)
