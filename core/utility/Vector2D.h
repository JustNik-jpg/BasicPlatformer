//
// Created by JustNik on 23 Jun 2022.
//

#pragma once

#include <string>
#include <valarray>

template<class T>
struct TVector2D {
    T x = 0;
    T y = 0;

    TVector2D() : x(0), y(0) {}

    TVector2D(T _x, T _y) : x(_x), y(_y) {}

    TVector2D(const TVector2D &v) : x(v.x), y(v.y) {}

    TVector2D &operator=(const TVector2D &v) = default;

    [[nodiscard]] T mag() const {
        return T(std::sqrt(x * x + y * y));
    }

    [[nodiscard]] T mag2() const {
        return x * x + y * y;
    }

    [[nodiscard]] TVector2D norm() const {
        T r = 1 / mag();
        return TVector2D(x * r, y * r);
    }

    [[nodiscard]] TVector2D perp() const {
        return (-y, x);
    }

    [[nodiscard]] TVector2D floor() const {
        return (std::floor(x), std::floor(y));
    }

    [[nodiscard]] TVector2D ceil() const {
        return (std::ceil(x), std::ceil(y));
    }

    [[nodiscard]] TVector2D max(const TVector2D &v) const {
        return (std::max(x, v.x), std::max(y, v.y));
    }

    [[nodiscard]] TVector2D min(const TVector2D &v) const {
        return (std::min(x, v.x), std::min(y, v.y));
    }

    TVector2D cart() {
        return {std::cos(y) * x, std::sin(y) * x};
    }

    TVector2D polar() {
        return {mag(), std::atan2(y, x)};
    }

    [[nodiscard]] T dot(const TVector2D &rhs) const {
        return this->x * rhs.x + this->y * rhs.y;
    }

    [[nodiscard]] T cross(const TVector2D &rhs) const {
        return this->x * rhs.y - this->y * rhs.x;
    }

    TVector2D operator+(const TVector2D &rhs) const {
        return TVector2D(this->x + rhs.x, this->y + rhs.y);
    }

    TVector2D operator-(const TVector2D &rhs) const {
        return TVector2D(this->x - rhs.x, this->y - rhs.y);
    }

    TVector2D operator*(const T &rhs) const {
        return TVector2D(this->x * rhs, this->y * rhs);
    }

    TVector2D operator*(const TVector2D &rhs) const {
        return TVector2D(this->x * rhs.x, this->y * rhs.y);
    }

    TVector2D operator/(const T &rhs) const {
        return TVector2D(this->x / rhs, this->y / rhs);
    }

    TVector2D operator/(const TVector2D &rhs) const {
        return TVector2D(this->x / rhs.x, this->y / rhs.y);
    }

    TVector2D &operator+=(const TVector2D &rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    TVector2D &operator-=(const TVector2D &rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    TVector2D &operator*=(const T &rhs) {
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }

    TVector2D &operator/=(const T &rhs) {
        this->x /= rhs;
        this->y /= rhs;
        return *this;
    }

    TVector2D &operator*=(const TVector2D &rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }

    TVector2D &operator/=(const TVector2D &rhs) {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }

    TVector2D operator+() const {
        return {+x, +y};
    }

    TVector2D operator-() const {
        return {-x, -y};
    }

    bool operator==(const TVector2D &rhs) const {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    bool operator!=(const TVector2D &rhs) const {
        return (this->x != rhs.x || this->y != rhs.y);
    }

    [[nodiscard]] std::string str() const {
        return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }

    friend std::ostream &operator<<(std::ostream &os, const TVector2D &rhs) {
        os << rhs.str();
        return os;
    }

    operator TVector2D<int32_t>() const {
        return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y)};
    }

    operator TVector2D<float>() const {
        return {static_cast<float>(this->x), static_cast<float>(this->y)};
    }

    operator TVector2D<double>() const {
        return {static_cast<double>(this->x), static_cast<double>(this->y)};
    }


};

template<class T>
inline TVector2D<T> operator*(const float &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs * (float) rhs.x), (T) (lhs * (float) rhs.y));
}

template<class T>
inline TVector2D<T> operator*(const double &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs * (double) rhs.x), (T) (lhs * (double) rhs.y));
}

template<class T>
inline TVector2D<T> operator*(const int &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs * (int) rhs.x), (T) (lhs * (int) rhs.y));
}

template<class T>
inline TVector2D<T> operator/(const float &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs / (float) rhs.x), (T) (lhs / (float) rhs.y));
}

template<class T>
inline TVector2D<T> operator/(const double &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs / (double) rhs.x), (T) (lhs / (double) rhs.y));
}

template<class T>
inline TVector2D<T> operator/(const int &lhs, const TVector2D<T> &rhs) {
    return TVector2D<T>((T) (lhs / (int) rhs.x), (T) (lhs / (int) rhs.y));
}

template<class T, class U>
inline bool operator<(const TVector2D<T> &lhs, const TVector2D<U> &rhs) {
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

template<class T, class U>
inline bool operator>(const TVector2D<T> &lhs, const TVector2D<U> &rhs) {
    return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x);
}

typedef TVector2D<int32_t> IVector2D;
typedef TVector2D<uint32_t> UIVector2D;
typedef TVector2D<float> FVector2D;
typedef TVector2D<double> DVector2D;