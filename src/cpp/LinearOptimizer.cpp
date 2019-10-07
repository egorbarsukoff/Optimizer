//
// Created by egor on 10/7/19.
//

#include "LinearOptimizer.h"

LinearOptimizer::LinearOptimizer(std::unique_ptr<Function> f, double step) : Optimizer(std::move(f),
                                                                                       std::make_unique<
                                                                                           NWithoutUpdates>(10)),
                                                                             init_step_size{step},
                                                                             step_size{step} {
    if (f->getDomain().dim() != 1) {
        throw std::runtime_error("Function must de dim 1");
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

