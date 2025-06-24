#include <chrono>
#include <iostream>
#include "LinearAlgebra.hpp"

using namespace LinearAlgebra;
using namespace std;

int main() {
    MemoryPool pool(8 * 1024 * 1024); // 8 MB
    size_t N = 500;
    Matrix A(N, N, &pool);
    Matrix B(N, N, &pool);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j) {
            A(i, j) = 1.0;
            B(i, j) = 2.0;
        }

    auto start = chrono::high_resolution_clock::now();
    Matrix C = A * B;
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Time taken: " << elapsed.count() << " sec" << endl;
}