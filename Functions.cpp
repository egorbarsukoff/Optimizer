//
// Created by eb on 09.10.2019.
//

#include "Functions.h"

double Rosenbrock::compute(const Eigen::VectorXd &x) const {
    return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
}

Eigen::VectorXd Rosenbrock::compute_grad(const Eigen::VectorXd &x) const {
    Eigen::VectorXd g(2);
    g << 400 * pow(x[0], 3) - 400 * x[0] * x[1] + 2 * x[0] - 2,
        200 * x[1] - 200 * x[0] * x[0];
    return g;
}

Eigen::MatrixXd Rosenbrock::compute_hess(const Eigen::VectorXd &x) const {
    Eigen::MatrixXd res(2, 2);
    res << -400 * (x[1] - x[0] * x[0]) + 800 * x[0] * x[0] + 2, -400 * x[0],
        -400 * x[0], 200;
    return res;
}

Rosenbrock::Rosenbrock(BoxDomain domain) : AbstractFunction(std::move(domain)) {}
