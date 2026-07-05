// vector_benchmark.cpp
//
// A minimal microbenchmark for std::vector: allocate a large contiguous buffer,
// time a sequential write pass (fill), then time a sequential read pass (sum).
//
// This is a starting point for systems-style C++ practice—measuring how basic
// memory access patterns behave before moving on to more complex workloads
// (matrix multiply, parsers, multithreading, etc.).
//
// What it does:
//   - Allocates a vector of 100,000,000 ints (contiguous heap storage).
//   - Fills each element with i % 100 to keep values in a small range.
//   - Sums all elements to exercise a read-heavy sequential scan.
//   - Reports fill time, sum time, and total in milliseconds via std::chrono.
//
// Why it matters:
//   - Write and read loops over the same buffer often differ in cost (stores vs
//     loads, cache state, prefetching, compiler optimizations).
//   - std::vector gives predictable, cache-friendly layout compared to pointer
//     chasing or fragmented allocations.
//   - Establishing a simple timing harness now makes later benchmarks easier
//     to compare apples-to-apples.
//
// Build & run (example):
//   g++ -std=c++17 -O2 cpp/vector_benchmark.cpp -o vector_benchmark && ./vector_benchmark

#include <chrono>
#include <iostream>
#include <vector>

int main() {
    // 1. Set vector size
    const std::size_t n = 100000000;

    // 2. Create vector
    std::vector<int> data(n);

    // 3. Measure fill time
    auto fill_start = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < n; ++i) {
        data[i] = static_cast<int>(i % 100);
    }

    auto fill_end = std::chrono::high_resolution_clock::now();

    // 4. Measure sum time
    auto sum_start = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    for (std::size_t i = 0; i < n; ++i) {
        sum += data[i];
    }

    auto sum_end = std::chrono::high_resolution_clock::now();

    // 5. Convert time to milliseconds
    auto fill_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(fill_end - fill_start)
            .count();

    auto sum_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(sum_end - sum_start)
            .count();

    // 6. Print results
    std::cout << "Vector size: " << n << "\n";
    std::cout << "Sum: " << sum << "\n";
    std::cout << "Fill time: " << fill_ms << "ms\n";
    std::cout << "Sum time: " << sum_ms << "ms\n";

    return 0;
}
