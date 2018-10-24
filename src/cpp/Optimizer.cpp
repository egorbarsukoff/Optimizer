//
// Created by egorb on 10.10.2018.
//

#include "../Optimizer.h"

Optimizer::Optimizer(const Function &f, Criterion& crit) : f(f.copy()), crit(crit.copy()), n(0) {}

Track Optimizer::optimize(const Vector &start) {
    track = Track();
    track.emplace_back(start, (*f)(start));
    crit.reset();
    while ((*crit)(track, n)) {
        step();
        ++n;
    }
    return track;
}