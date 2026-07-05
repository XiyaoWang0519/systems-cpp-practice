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

## matrix_multiply.cpp

This program benchmarks naive matrix multiplication at several sizes (`128`, `256`, `512`, `1024`). For each size it fills `A` with `1.0` and `B` with `2.0`, then times only the multiply step (not initialization).

For each output element `C[i][j]`, three nested loops compute the dot product of row `i` of `A` and column `j` of `B`. Matrices are stored as 1D `std::vector<double>`, so `A[i][j]` is `A[i * n + j]`. The algorithm is **O(n³)** and is **not optimized**—no blocking, SIMD, or parallelism.

Build and run:

```bash
g++ -std=c++17 -O2 cpp/matrix_multiply.cpp -o matrix_multiply
./matrix_multiply
```

Result on my MacBook Pro:

| Matrix size | C[0][0] | Time (ms) |
|-------------|---------|-----------|
| 128         | 256     | 1         |
| 256         | 512     | 15        |
| 512         | 1024    | 115       |
| 1024        | 2048    | 857       |