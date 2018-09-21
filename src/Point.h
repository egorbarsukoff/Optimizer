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


template <size_t n>
class Point {
    std::array<double, n> x;
public:
    explicit Point(std::array<double, n> x) : x(std::move(x)) {};
    Point() : x() {};
    Point(const Point& p) : Point(p.x) {};
    Point(Point&& p) noexcept : Point(std::move(p.x)) {};
    double operator[](size_t i) const {
        assert(i < x.size() && i >= 0);
        return x[i];
    }

    template <size_t dim>
    friend Point operator+(const Point<dim>& a, const Point<dim>& b);
};

template <size_t dim>
Point<dim> operator+(const Point<dim> &a, const Point<dim> &b) {
    assert(a.x.size() == b.x.size());
    Point<dim> result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), result.x.begin(), std::plus<>());
    return result;
}

template <size_t n>
using Track = std::vector<Point<n>>;


#endif //OPTIMIZER_POINT_H
