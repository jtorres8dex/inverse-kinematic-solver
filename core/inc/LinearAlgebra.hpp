#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>
#include "MemoryPool.hpp"

namespace LinearAlgebra {

class Vector;
class Matrix;

class Vector {
private:
    size_t size;
    double* data;
    MemoryPool* pool;

public:
    explicit Vector(size_t n, MemoryPool* allocator = nullptr)
        : size(n), pool(allocator) {
        if (pool)
            data = static_cast<double*>(pool->allocate(n * sizeof(double), alignof(double)));
        else
            data = new double[n];
    }

    double& operator[](size_t i) {
        assert(i < size);
        return data[i];
    }

    const double& operator[](size_t i) const {
        assert(i < size);
        return data[i];
    }

    Vector operator+(const Vector& other) const {
        assert(size == other.size);
        Vector result(size, pool);
        for (size_t i = 0; i < size; ++i)
            result[i] = data[i] + other[i];
        return result;
    }

    Vector operator-(const Vector& other) const {
        assert(size == other.size);
        Vector result(size, pool);
        for (size_t i = 0; i < size; ++i)
            result[i] = data[i] - other[i];
        return result;
    }

    Vector operator*(double scalar) const {
        Vector result(size, pool);
        for (size_t i = 0; i < size; ++i)
            result[i] = data[i] * scalar;
        return result;
    }

    Vector operator/(double scalar) const {
        assert(scalar != 0.0);
        Vector result(size, pool);
        for (size_t i = 0; i < size; ++i)
            result[i] = data[i] / scalar;
        return result;
    }

    double dot(const Vector& other) const {
        assert(size == other.size);
        double sum = 0.0;
        for (size_t i = 0; i < size; ++i)
            sum += data[i] * other[i];
        return sum;
    }

    size_t length() const { return size; }

    void print() const {
        std::cout << "[ ";
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "]\n";
    }

    ~Vector() {
        if (!pool)
            delete[] data;
    }
};

class Matrix {
private:
    size_t rows, cols;
    double* data;
    MemoryPool* pool;

public:
    Matrix(size_t r, size_t c, MemoryPool* allocator = nullptr)
        : rows(r), cols(c), pool(allocator) {
        if (pool)
            data = static_cast<double*>(pool->allocate(r * c * sizeof(double), alignof(double)));
        else
            data = new double[r * c];
    }

    static void MatrixMultiply(Matrix& result, const Matrix& A, const Matrix& B) {
        assert(A.numCols() == B.numRows());
        assert(result.numRows() == A.numRows());
        assert(result.numCols() == B.numCols());

        for (size_t i = 0; i < A.numRows(); ++i) {
            for (size_t j = 0; j < B.numCols(); ++j) {
                result(i, j) = 0.0;
                for (size_t k = 0; k < A.numCols(); ++k)
                    result(i, j) += A(i, k) * B(k, j);
            }
        }
    }

    double& operator()(size_t i, size_t j) {
        assert(i < rows && j < cols);
        return data[i * cols + j];
    }

    const double& operator()(size_t i, size_t j) const {
        assert(i < rows && j < cols);
        return data[i * cols + j];
    }

    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix result(rows, cols, pool);
        for (size_t i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix result(rows, cols, pool);
        for (size_t i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        assert(cols == other.rows);
        Matrix result(rows, other.cols, pool);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result(i, j) = 0.0;
                for (size_t k = 0; k < cols; ++k)
                    result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
        return result;
    }

    Vector operator*(const Vector& vec) const {
        assert(cols == vec.length());
        Vector result(rows, pool);
        for (size_t i = 0; i < rows; ++i) {
            result[i] = 0.0;
            for (size_t j = 0; j < cols; ++j)
                result[i] += (*this)(i, j) * vec[j];
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows, cols, pool);
        for (size_t i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    Matrix operator/(double scalar) const {
        assert(scalar != 0.0);
        Matrix result(rows, cols, pool);
        for (size_t i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] / scalar;
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols, rows, pool);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(j, i) = (*this)(i, j);
        return result;
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                std::cout << (*this)(i, j) << " ";
            std::cout << "\n";
        }
    }

    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

    static Matrix identity(size_t n, MemoryPool* allocator = nullptr) {
        Matrix I(n, n, allocator);
        for (size_t i = 0; i < n * n; ++i)
            I.data[i] = 0.0;
        for (size_t i = 0; i < n; ++i)
            I(i, i) = 1.0;
        return I;
    }

    ~Matrix() {
        if (!pool)
            delete[] data;
    }
};

} // namespace LinearAlgebra