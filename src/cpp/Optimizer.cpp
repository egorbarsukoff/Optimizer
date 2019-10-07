//
// Created by egorb on 10.10.2018.
//

#include "../Optimizer.h"

Optimizer::Optimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit_)
    : f(std::move(f)), crit(std::move(crit_)), n(0) {}

Track Optimizer::optimize(const Eigen::VectorXd &start) {
    reset();
    track = Track();
    track.emplace_back(start, (*f)(start));
    while ((*crit)(track, n)) {
        step();
        ++n;
    }
    return track;
}
void Optimizer::reset() {
    track = Track{};
    n = 0;
    crit->reset();
}
