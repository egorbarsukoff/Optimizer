//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_GRADIENT_H
#define OPTIMIZER_GRADIENT_H

#include <functional>
#include <iostream>
#include "Point.h"
#include "Function.h"

template <size_t dim>
class Gradient : public Point<dim>{
    const Point<dim>& from;
    double D(auto&& f) {
        double h = 0.01;
        return (f(h) - f(-h)) / (2*h);
    }
public:
    explicit Gradient<dim>(const Function<dim>& f, const Point<dim>& p) : from(p) {
        for (size_t i = 0; i < from.getX().size(); ++i) {
            this->x[i] = D([&](double h) {
                auto copy_p = p;
                copy_p[i] += h;
                return f(copy_p);
            });
        }
        for (auto a: Point<dim>::x) {
            std::cout << a << std::endl;
        }
    }

};


#endif //OPTIMIZER_GRADIENT_H
