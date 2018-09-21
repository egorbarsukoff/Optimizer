//
// Created by egorb on 21.09.2018.
//
#include <algorithm>
#include <functional>
#include <cassert>
#include "Point.h"

Point operator+(const Point &a, const Point &b) {
    assert(a.x.size() == b.x.size());
    Point result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), std::plus());
    return result;
}

double &Point::operator[](size_t i) {
    assert(i < x.size());
    return x[i];
}
