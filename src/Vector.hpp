#pragma ones

#ifndef OPENGLENGINE_VECTOR_HPP
#define OPENGLENGINE_VECTOR_HPP

#include <cmath>
#include <ostream>

class Vector {
public:
    Vector(size_t n) : data_size(n) {
        data = new float[n];
        for (int i = 0; i < n; ++i) {
            data[i] = 0;
        }
    }

    Vector(size_t n, float number) {
        data_size = n;
        data = new float[n];
        for (int i = 0; i < n; ++i) {
            data[i] = number;
        }
    }

    Vector(std::initializer_list<float> numbers) {
        data_size = numbers.size();
        data = new float[data_size];
        int i = 0;
        for (auto num: numbers) {
            data[i++] = num;
        }
    }

    Vector(size_t n, float *numbers) {
        data_size = n;
        data = new float[data_size];
        for (int i = 0; i < data_size; ++i) {
            data[i] = numbers[i];
        }
    }

    Vector(const Vector &other) {
        data_size = other.size();
        data = new float[data_size];
        for (int i = 0; i < data_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector() = default;

    Vector &operator=(const Vector &other) {
        if (this == &other) {
            return *this;
        }

        data_size = other.size();
        data = new float[data_size];
        for (int i = 0; i < size(); i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    float &operator[](const size_t idx) const {
        return data[idx];
    }

    Vector operator+(const Vector &other) const {
        check_sizes(other);

        float *new_data = new float[size()];
        for (int i = 0; i < size(); ++i) {
            new_data[i] = data[i] + other.data[i];
        }

        return Vector(size(), new_data);
    }

    Vector &operator+=(const Vector &other) {
        check_sizes(other);

        for (int i = 0; i < size(); ++i) {
            data[i] += other.data[i];
        }

        return *this;
    }

    Vector operator-(const Vector &other) const {
        check_sizes(other);

        float *new_data = new float[size()];
        for (int i = 0; i < size(); ++i) {
            new_data[i] = data[i] - other.data[i];
        }

        return Vector(size(), new_data);
    }

    Vector &operator-=(const Vector &other) {
        check_sizes(other);

        for (int i = 0; i < size(); ++i) {
            data[i] -= other.data[i];
        }

        return *this;
    }

    float scalar_product(const Vector &rhs) const {
        check_sizes(rhs);

        float scalar_product = 0;
        for (int i = 0; i < data_size; ++i) {
            scalar_product += data[i] * rhs.data[i];
        }

        return scalar_product;
    }

    static Vector cross_product(const Vector &lhs, const Vector &rhs) {
        if (lhs.size() != 3 || rhs.size() != 3) {
            throw std::runtime_error("Can't calculate the cross product. Dimension is not three");
        }

        return Vector{lhs.data[1] * rhs.data[2] - lhs.data[2] * rhs.data[1],
                      lhs.data[2] * rhs.data[0] - lhs.data[0] * rhs.data[2],
                      lhs.data[0] * rhs.data[1] - lhs.data[1] * rhs.data[0]
        };
    }

    Vector operator*(float other) const {
        auto *new_data = new float[size()];
        for (int i = 0; i < size(); ++i) {
            new_data[i] = data[i] * other;
        }

        return Vector(size(), new_data);
    }

    Vector &operator*=(float other) {
        for (int i = 0; i < size(); ++i) {
            data[i] *= other;
        }

        return *this;
    }

    Vector operator/(float other) const {
        if (other == 0) {
            throw std::runtime_error("Division by zero");
        }

        auto *new_data = new float[size()];
        for (int i = 0; i < size(); ++i) {
            new_data[i] = data[i] / other;
        }

        return Vector(size(), new_data);
    }

    Vector &operator/=(float other) {
        if (other == 0) {
            throw std::runtime_error("Division by zero");
        }

        for (int i = 0; i < size(); ++i) {
            data[i] /= other;
        }

        return *this;
    }

    bool operator==(const Vector &other) const {
        if (size() != other.size()) {
            return false;
        }

        for (int i = 0; i < size(); ++i) {
            if (data[i] != other.data[i]) return false;
        }

        return true;
    }

    bool operator!=(const Vector &other) const {
        return !(*this == other);
    }

    float length() const {
        float temp = 0;

        for (int i = 0; i < size(); ++i) {
            temp += std::pow(data[i], 2);
        }

        return std::sqrt(temp);
    }

    Vector normalize() const {
        if (length() == 0) {
            throw std::runtime_error("Can't normalize zero vector");
        }

        auto *new_data = new float[size()];
        for (int i = 0; i < size(); ++i) {
            new_data[i] = data[i] / length();
        }

        return Vector(size(), new_data);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector) {
        std::cout << std::setprecision(4) << std::fixed;

        os << "Vector[size=" << vector.size() << "]: [";
        for (int i = 0; i < vector.size(); ++i) {
            os << vector[i] << (i == vector.size() - 1 ? "]" : ", ");
        }
        return os;
    }

    size_t size() const {
        return data_size;
    }

    ~Vector() {
        delete[] data;
    }

private:
    float *data;
    size_t data_size;

    void check_sizes(const Vector &other) const {
        if (size() != other.size()) {
            throw std::runtime_error("Vector sizes are not equal");
        }
    }
};

#endif //OPENGLENGINE_VECTOR_HPP