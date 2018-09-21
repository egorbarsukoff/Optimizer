//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Point.h"
#include "Function.h"

class Optimizer {
    Criterion crit;
    virtual void step() = 0;
public:
    explicit Optimizer(const Criterion& crit) : crit(crit) {}
    Track optimize(Function f, Point start);
};


#endif //OPTIMIZER_OPTIMIZER_H
