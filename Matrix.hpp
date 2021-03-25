#pragma ones

#include <cmath>
#include <iostream>
#include <iomanip>
#include "Vector.hpp"

class Matrix {
public:
    Matrix(size_t n) : data_size(n) {
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * n]);
        for (int i = 0; i < n; ++i) {
            data[i] = Vector(n);
        }
    }

    Matrix(size_t n, float number): data_size(n) {
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

    Matrix(size_t n, float **numbers) : data_size(n) {
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * data_size]);

        for (int row = 0; row < data_size; ++row) {
            data[row] = Vector(data_size, numbers[row]);
        }
    }

    Matrix(const Matrix &other) {
        data_size = other.size();
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * data_size]);

        for (int row = 0; row < data_size; ++row) {
            data[row] = Vector(data_size);
        }

        for (int i = 0; i < data_size; ++i) {
            for (int j = 0; j < data_size; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix &operator=(const Matrix &other) {
        data_size = other.size();
        data = reinterpret_cast<Vector *>(new char[sizeof(Vector) * data_size]);

        for (int row = 0; row < data_size; ++row) {
            data[row] = Vector(data_size);
        }

        for (int i = 0; i < data_size; ++i) {
            for (int j = 0; j < data_size; ++j) {
                data[i][j] = other.data[i][j];
            }
        }

        return *this;
    }

    Vector &operator[](const size_t idx) const {
        return data[idx];
    }

    Matrix operator+(const Matrix &other) const {
        check_sizes(other);

        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator+=(const Matrix &other) {
        check_sizes(other);

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] += other.data[i][j];
            }
        }

        return *this;
    }

    Matrix operator+(float other) const {
        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] + other;
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator+=(float other) {
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] += other;
            }
        }

        return *this;
    }

    Matrix operator-(const Matrix &other) const {
        check_sizes(other);

        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator-=(const Matrix &other) {
        check_sizes(other);

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] -= other.data[i][j];
            }
        }

        return *this;
    }

    Matrix operator-(float other) const {
        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] - other;
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator-=(float other) {
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] -= other;
            }
        }

        return *this;
    }

    Matrix operator*(float other) const {
        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] * other;
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator*=(float other) {
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] *= other;
            }
        }

        return *this;
    }

    Matrix operator*(const Matrix &other) const {
        check_sizes(other);

        Matrix new_data(size());

        for (int i = 0; i < size(); ++i) {
            Vector row = this->get_row(i);
            for (int j = 0; j < size(); ++j) {
                Vector col = other.get_col(j);
                for (int k = 0; k < size(); ++k) {
                    new_data[i][j] += row[k] * col[k];
                }
            }
        }

        return new_data;
    }

    Matrix &operator*=(const Matrix &other) {
        check_sizes(other);

        Matrix new_data(size());

        for (int i = 0; i < size(); ++i) {
            Vector row = data[i];
            for (int j = 0; j < size(); ++j) {
                Vector col = other.get_col(j);
                for (int k = 0; k < size(); ++k) {
                    new_data[i][j] += row[k] * col[k];
                }
            }
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] = new_data[i][j];
            }
        }

        return *this;
    }

    Vector operator*(const Vector &other) const {
        if (size() != other.size()) {
            throw std::runtime_error("Matrix and vector sizes are not equal");
        }

        Vector vector(size());

        for (int i = 0; i < size(); ++i) {
            Vector row = data[i];
            for (int j = 0; j < size(); ++j) {
                vector[i] += row[j] * other[j];
            }
        }

        return vector;
    }

    Matrix operator/(float other) const {
        if (other == 0) {
            throw std::runtime_error("Division by zero");
        }

        Matrix new_data(size());
        for (int row = 0; row < size(); ++row) {
            new_data[row] = Vector(size());
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                new_data[i][j] = data[i][j] / other;
            }
        }

        return Matrix(new_data);
    }

    Matrix &operator/=(float other) {
        if (other == 0) {
            throw std::runtime_error("Division by zero");
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data[i][j] /= other;
            }
        }

        return *this;
    }

    bool operator==(const Matrix &other) const {
        if (size() != other.size()) {
            return false;
        }

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                if (data[i][j] != other.data[i][j]) return false;
            }
        }

        return true;
    }

    bool operator!=(const Matrix &other) const {
        return !(*this == other);
    }

    static Matrix identity_matrix(size_t n) {
        Matrix mat(n);
        for (int i = 0; i < mat.size(); ++i) {
            mat[i][i] = 1;
        }

        return mat;
    }

    Matrix transposed() {
        float temp;

        for (int i = 0; i < size(); ++i) {
            for (int j = i; j < size(); ++j) {
                temp = data[i][j];
                data[i][j] = data[j][i];
                data[j][i] = temp;
            }
        }
        return *this;
    }

    float determinant() const {
        return find_determinant(*this, size());
    }

    Matrix adjugate() const {
        Matrix adjugate(size());

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                Matrix Mat_ij(size() - 1);

                int idx = 0;
                for (int k = 0; k < size(); ++k) {
                    for (int l = 0; l < size(); ++l) {
                        if (k == i || l == j) {
                            continue;
                        }
                        Mat_ij[idx / (size() - 1)][idx % (size() - 1)] = data[k][l];
                        idx++;
                    }
                }

                adjugate[i][j] = Mat_ij.determinant() * std::pow(-1, i + j + 2);
            }
        }

        return adjugate;
    }

    Matrix inverse() {
        float det = this->determinant();
        if (det == 0) {
            throw std::runtime_error("Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix new_matrix = this->adjugate().transposed();

        return new_matrix * (1 / det);
    }

    static Matrix transform(const Vector &other) {
        if (other.size() != 3) {
            throw std::runtime_error("Can't make matrix. Vector dimension is not three");
        }

        Matrix matrix = identity_matrix(4);
        for (int i = 0; i < 3; ++i) {
            matrix[i][3] = other[i];
        }

        return matrix;
    }

    static Matrix scale(const Vector &other) {
        if (other.size() != 3) {
            throw std::runtime_error("Can't make matrix. Vector dimension is not three");
        }

        Matrix matrix(4);
        for (int i = 0; i < 3; ++i) {
            matrix[i][i] = other[i];
        }
        matrix[3][3] = 1;

        return matrix;
    }



    static Matrix rotate(const float &alpha, const float &beta, const float &gamma) {
        Matrix x_matrix = identity_matrix(4);
        Matrix y_matrix = identity_matrix(4);
        Matrix z_matrix = identity_matrix(4);

        x_matrix[1][1] = cos(alpha);
        x_matrix[1][2] = -sin(alpha);
        x_matrix[2][1] = sin(alpha);
        x_matrix[2][2] = cos(alpha);

        y_matrix[0][0] = cos(beta);
        y_matrix[0][2] = sin(beta);
        y_matrix[2][0] = -sin(beta);
        y_matrix[2][2] = cos(beta);

        z_matrix[0][0] = cos(gamma);
        z_matrix[0][1] = -sin(gamma);
        z_matrix[1][0] = sin(gamma);
        z_matrix[1][1] = cos(gamma);

        return x_matrix * y_matrix * z_matrix;
    }

    static Matrix look_at(const Vector &from, const Vector &to, const Vector &world_up) {
        Vector forward = (from - to).normalize();
        world_up.normalize();
        Vector right = Vector::cross_product(world_up, forward).normalize();
        Vector up = Vector::cross_product(forward, right).normalize();

        Matrix matrix = identity_matrix(4);
        for (int i = 0; i < 3; ++i) {
            matrix[0][i] = right[i];
            matrix[1][i] = up[i];
            matrix[2][i] = forward[i];
            matrix[3][i] = from[i];
        }

        return matrix;
    }



    static Matrix perspective(const float &fov, const float &ratio, const float &near, const float &far) {
        Matrix matrix(4);

        matrix[0][0] = 1 / (ratio * tan(fov / 2));
        matrix[1][1] = 1 / tan(fov / 2);
        matrix[2][2] = (near + far) / (near - far);
        matrix[2][3] = -1;
        matrix[3][2] = (2 * far * near) / (near - far);

        return matrix;
    }

    static Matrix ortho(const float &right, const float &left, const float &top, const float &bottom, const float &near, const float &far) {
        Matrix matrix = identity_matrix(4);

        matrix[0][0] = -2 / (right - left);
        matrix[0][3] = (right + left) / (right - left);
        matrix[1][1] = -2 / (top - bottom);
        matrix[1][3] = (top + bottom) / (top - bottom);
        matrix[2][2] = -2 / (far - near);
        matrix[2][3] = - (far + near) / (far - near);

        return matrix;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        std::cout << std::setprecision(4) << std::fixed;

        os << "Matrix[size=" << matrix.size() << "x" << matrix.size() << "]: [";
        for (int i = 0; i < matrix.size(); ++i) {
            os << "[";
            for (int j = 0; j < matrix.size(); ++j) {
                std::string end = (j == matrix.size() - 1 ? "], " : ", ");
                if (i == matrix.size() - 1 && i == j) {
                    end = "]]";
                }
                os << matrix[i][j] << end;
            }
        }
        return os;
    }

    Vector get_row(size_t n) const {
        return data[n];
    }

    Vector get_col(size_t n) const {
        Vector vector(size());

        for (int i = 0; i < size(); ++i) {
            vector[i] = data[i][n];
        }

        return vector;
    }

    size_t size() const {
        return data_size;
    }

    ~Matrix() {
        delete data;
    }

private:
    Vector *data;
    size_t data_size;

    void check_sizes(const Matrix &other) const {
        if (size() != other.size()) {
            throw std::runtime_error("Matrix sizes are not equal");
        }
    }

    float find_determinant(const Matrix &mat, size_t n) const {
        if (n == 1) {
            return mat[0][0];
        }

        if (n == 2) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }

        float determinant = 0;
        for (int i = 0; i < n; i++) {
            Matrix temp(n - 1);
            for (int j = 1; j < n; j++) {
                int idx = 0;
                for (int k = 0; k < n; k++) {
                    if (k == i) {
                        continue;
                    }

                    temp[j - 1][idx++] = mat[j][k];
                }
            }

            determinant += pow(-1, i + 2) * mat[0][i] * find_determinant(temp, n - 1);
        }

        return determinant;
    }
};
