#include <cmath>

#include "Vector.hpp"

class Matrix {
  public:
    Matrix(size_t n) : data_size(n) {
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * n]);
        for (int i = 0; i < n; ++i) {
            data[i] = Vector(n);
        }
    }

    Matrix(size_t n, float number) {
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * n]);
        for (int i = 0; i < n; ++i) {
            data[i] = Vector(n, number);
        }
    }

    Matrix(std::initializer_list<float> numbers) {
        double d_size = std::sqrt(numbers.size());
        if (d_size * d_size != numbers.size()) {
            throw std::runtime_error("Matrix size is not correct");
        }

        data_size = static_cast<size_t>(std::sqrt(numbers.size()));
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * data_size]);

        for (int row = 0; row < data_size; ++row) {
            data[row] = Vector(data_size);
        }

        int idx = 0;
        for (auto num: numbers) {
            data[idx / data_size][idx % data_size] = num;
            idx++;
        }
    }

//    Matrix(size_t n, float *numbers) {
//        data_size = n;
//        data = new float[data_size];
//        for (int i = 0; i < data_size; ++i) {
//            data[i] = numbers[i];
//        }
//    }
//
//    Matrix(const Matrix &other) {
//        check_sizes(other);
//
//        delete[] data;
//
//        data_size = n;
//        data = new float[data_size];
//        for (int i = 0; i < size(); i++) {
//            data[i] = other.data[i];
//        }
//
//        return *this;
//    }


  private:
    Vector *data;
    size_t data_size;

    void check_sizes(const Matrix &other) const {

    }
};

// Конструкторы: Mati(), Mati(float)m Mati(float, float, ...), Mati(Mati)
// сложение матриц
// вычитание матриц
// умножение матриц
// умножение на число
// деление на число
// прибавления числа
// вычитание числа
// умножение матрицы на вектор
// единичная матрица
// обратная матрица
// транспонированная матрица
// сравнение векторов ==, !=
// смещение
// поворот
// масштабирование
// получить строку/столбец

// Доп. методы
// LookAt
// Perspective
// Ortho