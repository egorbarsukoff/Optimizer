//
// Created by egorb on 10.10.2018.
//

#include "../Optimizer.h"

Optimizer::Optimizer(std::unique_ptr<Function> f, std::unique_ptr<Criterion> crit)
    : f(std::move(f)), crit(std::move(crit)), n(0) {}

Track Optimizer::optimize(const std::valarray<double> &start) {
    track = Track();
    track.emplace_back(start, (*f)(start));
    crit->reset();
    while ((*crit)(track, n)) {
        step();
        ++n;
    }
    return track;
}