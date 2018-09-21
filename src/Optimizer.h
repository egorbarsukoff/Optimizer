//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Point.h"
#include "Function.h"

template <size_t dim>
class Optimizer {
    const Criterion<dim>& crit;
    virtual void step() = 0;
public:
    explicit Optimizer(const Criterion<dim>& crit) : crit(crit) {}
    Track<dim> optimize(const Function<dim> &f, const Point<dim> &start) {
        Track<dim> track;
        track.push_back(start);
        while (crit(track)) {
            step();
        }
        return track;
    }
};


#endif //OPTIMIZER_OPTIMIZER_H
