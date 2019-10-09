//
// Created by egorb on 10.10.2018.
//

#include "optim/Optimizer.h"

Optimizer::Optimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit_)
    : f(std::move(f)), crit(std::move(crit_)), n(0) {}

Track Optimizer::optimize(const Eigen::VectorXd &start) {
    reset();
    track = Track();
    track.emplace_back(start, (*f)(start));
    bool finished = false;
    while (!finished && (*crit)(track, n)) {
        finished = step();
        ++n;
    }
    return track;
}
void Optimizer::reset() {
    track = Track{};
    n = 0;
    crit->reset();
}
void Optimizer::set_f(std::unique_ptr<const AbstractFunction> f) {
    Optimizer::reset();
    Optimizer::f = std::move(f);
}
