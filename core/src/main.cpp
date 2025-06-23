#include "LinearAlgebra.hpp"

using namespace LinearAlgebra;
using namespace std;

int main() {
    MemoryPool pool(4096);

    Matrix A = Matrix::identity(3, &pool);
    Vector v(3, &pool);
    v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;
    v.print();
    Vector result = A * v;
    cout << "matrix times a vec: ";
    result.print();

    Matrix B(3, 3, &pool);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            B(i, j) = i + j;

    Matrix C = A + B;
    C.print();

    
}