//
// Created by eb on 09.10.2019.
//

#include "optim/NewtonOptimizer.h"
#include <Eigen/Dense>
#include <iostream>

bool NewtonOptimizer::step() {
    auto &x = track.back().x;
    Eigen::VectorXd p;
    Eigen::VectorXd antigrad = -f->gradient(x);
    Eigen::MatrixXd hess = f->hessian(x);
    if (abs(hess.determinant()) < 1e-10) {
        p = antigrad;
    } else {
        p = hess.inverse() * antigrad;
    }
    try {
        p *= f->getDomain().intersectCoeff(x, p);
    } catch (std::runtime_error &e) {
        return true;
    }
    linOpt.set_f(std::make_unique<Function>(BoxDomain{{{0, 1}}}, [this, &p, &x](const auto &a) {
        return (*f)(x + p * a[0]);
    }));
    auto linOptRes = linOpt.optimize(Eigen::VectorXd::Zero(1)).back();
    Eigen::VectorXd new_x = x + p * linOptRes.x[0];
    track.emplace_back(new_x, linOptRes.y);
    return false;
}

void NewtonOptimizer::reset() {
    Optimizer::reset();
    linOpt.set_f(std::unique_ptr<AbstractFunction>(nullptr));
}

NewtonOptimizer::NewtonOptimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit)
    : Optimizer(std::move(f), std::move(crit)) {}
