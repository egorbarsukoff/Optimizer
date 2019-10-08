//
// Created by egor on 10/7/19.
//

#include "optim/LinearOptimizer.h"

LinearOptimizer::LinearOptimizer(std::unique_ptr<AbstractFunction> f, double step) : Optimizer(std::move(f),
                                                                                               std::make_unique<
                                                                                           NWithoutUpdates>(10)),
                                                                                     init_step_size(
                                                                                 Eigen::VectorXd::Ones(1) * step),
                                                                                     step_size(
                                                                                 Eigen::VectorXd::Ones(1) * step) {
    if (f->getDomain().dim() != 1) {
        throw std::runtime_error("AbstractFunction must de dim 1");
    }
}

void LinearOptimizer::step() {
    auto x = track.back().x + step_size;
    if (!f->getDomain().inDomain(x)) {
        step_size = f->getDomain().intersectCoeff(x, step_size) * step_size * 0.99;
    }
    if (auto y = (*f)(x); track.back().y > y) {
        track.emplace_back(x, y);
    } else {
        step_size /= 2;
    }
}
void LinearOptimizer::reset() {
    Optimizer::reset();
    step_size = init_step_size;
}

