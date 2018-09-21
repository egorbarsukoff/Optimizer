//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_POINT_H
#define OPTIMIZER_POINT_H

#include <vector>


using Track = std::vector<Point>;


class Point {
    std::vector<double> x;
public:
    explicit Point(std::vector<double> x) : x(std::move(x)) {};
    Point() : x() {};
    Point(const Point& p) : Point(p.x) {};
    Point(Point&& p) noexcept : Point(std::move(p.x)) {};
    double& operator[] (size_t i);
    friend Point operator+(const Point& a, const Point& b);
};


#endif //OPTIMIZER_POINT_H
