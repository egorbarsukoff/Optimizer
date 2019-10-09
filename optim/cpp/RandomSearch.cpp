//
// Created by egorb on 10.10.2018.
//

#include "optim/RandomSearch.h"

bool RandomSearch::step() {
    Eigen::VectorXd new_point(track.back().x.size());
    bool close_good = false;
    if (Random::getB(p))
        new_point = Optimizer::f->getDomain().randomPoint();
    else {
        new_point = (BoxDomain(Optimizer::track.back().x, delta) * Optimizer::f->getDomain()).randomPoint();
        close_good = true;
    }
    double t;
    if ((t = (*f)(new_point)) < (*f)(Optimizer::track.back().x)) {
        Optimizer::track.emplace_back(std::move(new_point), t);
        if (close_good)
            delta *= 0.9;

    }
    return false;
}

RandomSearch::RandomSearch(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit, double h, double p) :
    Optimizer(std::move(f), std::move(crit)), p(p) {
    delta = pow(Optimizer::f->getDomain().measure(), 1. / 2) * h;
}
