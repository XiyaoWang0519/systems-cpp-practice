#include <chrono>
#include <iostream>
#include <vector>

int main() {
    const std::size_t n = 512;

    // A, B, C are n x n matrices stored as 1D vectors.
    std::vector<double> A(n * n);
    std::vector<double> B(n * n);
    std::vector<double> C(n * n, 0.0);

    // Initialize A and B.
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            A[i * n + j] = 1.0;
            B[i * n + j] = 2.0;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Naive matrix multiplication:
    // C[i][j] = sum over k of A[i][k] * B[k][j]
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            double sum = 0.0;
            for (std::size_t k = 0; k < n; ++k) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Matrix size: " << n << "x" << n << "\n";
    std::cout << "C[0][0] = " << C[0] << "\n";
    std::cout << "Time taken: " << elapsed_ms << " milliseconds\n";

    return 0;
}
