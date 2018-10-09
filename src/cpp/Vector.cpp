//
// Created by egorb on 10.10.2018.
//
#include <iostream>
#include "../Vector.h"

Vector::Vector(std::vector<double> x) : x(std::move(x)) {};

Vector::Vector(size_t dim) : x(dim) {}

Vector::Vector(const Vector& p) : Vector(p.x) {}

Vector::Vector(Vector&& p) noexcept : Vector(std::move(p.x)) {}

Vector::Vector(size_t dim, size_t n) : Vector(dim) {
        x[n] = 1;
}

const std::vector<double>& Vector::getX() const {
    return x;
}

size_t Vector::getDim() const {
    return x.size();
}

double Vector::norm() const {
    double sum = 0;
    for (double i : x)
        sum += i*i;
    return pow(sum, 1./2);
}

double Vector::operator[](size_t i) const {
    assert(i < x.size() && i >= 0);
    return x[i];
}

double& Vector::operator[](size_t i) {
    assert(i < x.size() && i >= 0);
    return x[i];
}

std::ostream& operator<<(std::ostream& o, const Vector& p) {
    o << "( ";
    for (auto x : p.x) {
        o << x << " ";
    }
    o << ")";
}

Vector pairWiseTransform(const Vector &a, const Vector &b, std::function<double(double, double)> f) {
    assert(a.x.size() == b.x.size());
    Vector result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), result.x.begin(), f);
    return result;
}

Vector operator+(const Vector &a, const Vector &b) {
    return pairWiseTransform(a, b, std::plus<double>());
}

Vector operator-(const Vector &a, const Vector &b) {
    return pairWiseTransform(a, b, std::minus<double>());
}

Vector operator*(Vector p, double a) {
    std::transform(p.x.begin(), p.x.end(), p.x.begin(), std::bind1st(std::multiplies<double>(), a));
    return p;
}