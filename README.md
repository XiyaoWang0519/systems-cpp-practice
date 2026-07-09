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
- latency timer

Completed exercises:
- vector benchmark
- naive matrix multiplication
- CSV parser
- latency timer
- multithreaded sum

## Build with CMake

Configure and build all exercises from the repository root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Run an individual exercise from the build directory, for example:

```bash
./build/multithread_sum
```

The CSV parser needs the sample data path when run from the repository root:

```bash
./build/csv_parser data/sample_metrics.csv
```

Verified with CMake 4.2.1 and AppleClang 17.0.0. All five targets built and ran successfully. Timing results below are from this one Release build run and will vary between runs.

## vector_benchmark.cpp

Result on my MacBook Pro:

- Vector size: 100,000,000 integers
- Sum: 4,950,000,000
- Fill time: 30 ms
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
| 128         | 256     | 3         |
| 256         | 512     | 20        |
| 512         | 1024    | 123       |
| 1024        | 2048    | 935       |

## csv_parser.cpp

This program reads benchmark-style metrics from a CSV file and computes basic statistics.

It reads `data/sample_metrics.csv` (or a path passed on the command line), skips the header row, parses each row into a `Row` struct (`name`, `latency_ms`, `throughput_tokens_per_sec`), and reports:

- average latency
- max latency (with run name)
- average throughput
- max throughput (with run name)

Malformed rows are skipped and counted.

Build and run:

```bash
g++ -std=c++17 -O2 -Wall -Wextra cpp/csv_parser.cpp -o csv_parser
./csv_parser
```

Result on my MacBook Pro:

```
Parsed rows: 5
Skipped rows: 0

Average latency: 14.10 ms
Max latency: 18.30 ms (run_4)

Average throughput: 79.00 tokens/sec
Max throughput: 88.40 tokens/sec (run_3)
```

## latency_timer.cpp

This program defines a reusable `Timer` class (`start`, `stop`, `elapsed_ms`) built on `std::chrono::steady_clock`, then uses it to time summing a `std::vector<int>` of 100,000,000 elements.

`start_time` and `end_time` are private members, and `elapsed_ms` is a `const` member function that returns the duration between them in milliseconds. Setup (filling the vector) happens before `timer.start()`, so only the summation loop is measured.

Build and run:

```bash
g++ -std=c++17 -O2 cpp/latency_timer.cpp -o cpp/latency_timer
./cpp/latency_timer
```

Result on my MacBook Pro:

```
sum = 100000000
elapsed time = 27.3639 ms
```

This only measures the sum loop, not vector construction/fill, and is a single run rather than an average over multiple trials.

## multithread_sum.cpp

This program compares summing a large `std::vector<int>` with one thread versus four threads.

The multithreaded version splits the vector into contiguous chunks, starts one `std::thread` per chunk, stores each partial sum in a separate slot, joins all threads, and then combines the partial sums.

Build and run:

```bash
g++ -std=c++17 -O2 -pthread cpp/multithread_sum.cpp -o cpp/multithread_sum
./cpp/multithread_sum
```

Result on my MacBook Pro:

```
data size = 100000000
num_threads = 4

single-thread sum = 100000000
multi-thread sum  = 100000000

single-thread time = 23.4063 ms
multi-thread time  = 3.15829 ms

result: correct
```

This is a simple thread-splitting exercise, not a full benchmark. The timing is from one run, so it can vary between runs.
