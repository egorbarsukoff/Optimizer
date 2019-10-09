//
// Created by egor on 10/7/19.
//

#include <iostream>
#include "optim/LinearOptimizer.h"

LinearOptimizer::LinearOptimizer(std::unique_ptr<AbstractFunction> f_, double step) :
    Optimizer(std::move(f_), std::make_unique<NWithoutUpdates>(10)),
    init_step_size(Eigen::VectorXd::Ones(1) * step),
    step_size(Eigen::VectorXd::Ones(1) * step) {
    if (f && f->getDomain().dim() != 1) {
        throw std::runtime_error("AbstractFunction must de dim 1");
    }
}

void LinearOptimizer::step() {
    Eigen::VectorXd x = track.back().x + step_size;
    x[0] = std::clamp(x[0], f->getDomain()[0][0], f->getDomain()[0][1]);
    if (auto y = (*f)(x); track.back().y > y) {
        track.emplace_back(x, y);
    } else {
        step_size /= -2;
    }
}
void LinearOptimizer::reset() {
    Optimizer::reset();
    step_size = init_step_size;
}

