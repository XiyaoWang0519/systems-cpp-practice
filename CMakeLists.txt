cmake_minimum_required(VERSION 3.16)

project(systems_cpp_practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(vector_benchmark
    cpp/vector_benchmark.cpp
)

add_executable(matrix_multiply
    cpp/matrix_multiply.cpp
)

add_executable(csv_parser
    cpp/csv_parser.cpp
)

add_executable(latency_timer
    cpp/latency_timer.cpp
)

add_executable(multithread_sum
    cpp/multithread_sum.cpp
)

target_link_libraries(multithread_sum
    PRIVATE Threads::Threads
)
