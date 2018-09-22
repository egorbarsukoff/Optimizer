//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include "Point.h"
#include "BoxDomain.h"
#include "Gradient.h"

template <size_t dim>
class Function {
protected:
    BoxDomain<dim> domain;
    virtual double compute(const Point<dim>& x) const = 0;
public:
    double operator()(const Point<dim> &x) const {
        if (domain.inDomain(x)) {
            return compute(x);
        } else
            throw "Out of bounds";
    }
};

class Rosenbrock : public Function<2> {
    double compute(const Point<2>& x) const override {
        return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
    }
};


#endif //OPTIMIZER_FUNCTION_H
