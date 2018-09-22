//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_POINT_H
#define OPTIMIZER_POINT_H

#include <array>
#include <vector>
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <functional>


template <size_t dim>
class Point;

template <size_t dim>
Point<dim> pairWiseTransform(const Point<dim> &a, const Point<dim> &b, std::function<double(double, double)> f);



template <size_t dim>
class Point {
protected:
    std::array<double, dim> x;
public:
    explicit Point(std::array<double, dim> x) : x(std::move(x)) {};
    Point() : x() {};
    Point(const Point& p) : Point(p.x) {};
    Point(Point&& p) noexcept : Point(std::move(p.x)) {};
    Point(size_t n) {
        x[n] = 1;
    }

    const std::array<double, dim> &getX() const {
        return x;
    }

    double operator[](size_t i) const {
        assert(i < x.size() && i >= 0);
        return x[i];
    }
    double& operator[](size_t i) {
        assert(i < x.size() && i >= 0);
        return x[i];
    }
    Point operator*(double a) {
        std::transform(x.begin(), x.end(), x.begin(), std::bind1st(std::multiplies<double>(), a));
    }

    template <size_t n>
    friend Point<n> pairWiseTransform(const Point<n> &a, const Point<n> &b, std::function<double(double, double)> f);
};


template <size_t dim>
Point<dim> pairWiseTransform(const Point<dim> &a, const Point<dim> &b, std::function<double(double, double)> f) {
    assert(a.x.size() == b.x.size());
    Point<dim> result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), result.x.begin(), f);
    return result;
}

template <size_t dim>
Point<dim> operator+(const Point<dim> &a, const Point<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::plus<double>());
}

template <size_t dim>
Point<dim> operator-(const Point<dim> &a, const Point<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::minus<double>());
}

template <size_t n>
using Track = std::vector<Point<n>>;


#endif //OPTIMIZER_POINT_H
