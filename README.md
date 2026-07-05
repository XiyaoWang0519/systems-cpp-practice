# systems-cpp-practice

This repo is my C++ systems practice repo for AI infrastructure / accelerator systems preparation.

Current focus:
- basic C++ syntax and STL
- benchmarking with chrono
- memory and runtime behavior
- small utilities for future performance projects

Planned exercises:
- vector benchmark
- naive matrix multiplication
- CSV parser
- latency timer
- simple multithreading example

## vector_benchmark.cpp

Result on my MacBook Pro:

- Vector size: 100,000,000 integers
- Sum: 4,950,000,000
- Fill time: 16 ms
- Sum time: 5 ms

The program fills a large `std::vector<int>` and then sums all elements.

The fill phase measures sequential write performance.
The sum phase measures sequential read performance plus simple integer accumulation.