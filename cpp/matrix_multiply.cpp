#include <chrono>
#include <iostream>
#include <vector>

// Naive matrix multiplication: C = A × B, where A, B, and C are n×n matrices
// stored as 1D vectors. Only the multiply loop is timed.
void multiply(std::size_t n,
              const std::vector<double>& A,
              const std::vector<double>& B,
              std::vector<double>& C) {
    // i = row index of the output C (and of A)
    // j = column index of the output C (and of B)
    // k = index along the shared inner dimension (column of A, row of B)
    //
    // A[i][k] lives at A[i * n + k]: row i starts at offset i*n in the flat array,
    // and element k within that row is k positions further.
    //
    // Three nested loops each run n times → O(n^3) total work.
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            double sum = 0.0;
            for (std::size_t k = 0; k < n; ++k) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

int main() {
    const std::size_t sizes[] = {128, 256, 512, 1024};

    for (std::size_t n : sizes) {
        std::vector<double> A(n * n);
        std::vector<double> B(n * n);
        std::vector<double> C(n * n, 0.0);

        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                A[i * n + j] = 1.0;
                B[i * n + j] = 2.0;
            }
        }

        auto start = std::chrono::steady_clock::now();
        multiply(n, A, B, C);
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Matrix size: " << n << "x" << n << "\n";
        std::cout << "C[0][0] = " << C[0] << "\n";
        std::cout << "Time taken: " << elapsed_ms << " milliseconds\n\n";
    }

    return 0;
}
