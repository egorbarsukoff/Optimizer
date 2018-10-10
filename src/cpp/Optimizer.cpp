//
// Created by egorb on 10.10.2018.
//

#include "../Optimizer.h"

Optimizer::Optimizer(const Function &f, Criteria& crit) : f(f), crit(crit), n(0) {}

Track Optimizer::optimize(const Vector &start) {
    track = Track();
    track.emplace_back(start, f(start));
    while (crit(track, n)) {
        step();
        ++n;
    }
    return track;
}