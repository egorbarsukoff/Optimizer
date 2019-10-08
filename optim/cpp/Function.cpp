//
// Created by egorb on 10.10.2018.
//


#include "optim/Function.h"

AbstractFunction::AbstractFunction(BoxDomain domain) : domain(std::move(domain)) {}

const BoxDomain &AbstractFunction::getDomain() const {
    return domain;
}

double AbstractFunction::operator()(const Eigen::VectorXd &x) const {
    return checkBoxAndCall([this](auto &&x) { return compute(x); }, x);
}

Eigen::VectorXd AbstractFunction::gradient(const Eigen::VectorXd &x) const {
    return checkBoxAndCall([this](auto &&x) { return compute_grad(x); }, x);
}

Eigen::MatrixXd AbstractFunction::hessian(const Eigen::VectorXd &x) const {
    return checkBoxAndCall([this](auto &&x) { return compute_hess(x); }, x);
}

Eigen::VectorXd AbstractFunction::compute_grad(const Eigen::VectorXd &x) const {
    return num_grad(x);
}

Eigen::MatrixXd AbstractFunction::compute_hess(const Eigen::VectorXd &x) const {
    return num_hess(x);
}

Eigen::VectorXd AbstractFunction::num_grad(const Eigen::VectorXd &x) const {
    Eigen::VectorXd ans(this->domain.dim());
    for (size_t i = 0; i < static_cast<size_t>(x.size()); ++i) {
        ans[i] = D([&](double h) {
            Eigen::VectorXd ix = Eigen::VectorXd::Zero(x.size());
            ix[i] = 1;
            return (*this)(x + ix * h);
        });
    }
    return ans;
}

Eigen::MatrixXd AbstractFunction::num_hess(const Eigen::VectorXd &x) const {
    Eigen::MatrixXd res(x.size(), x.size());
    for (long int i = 0; i < x.size(); ++i) {
        for (long int j = 0; j <= i; ++j) {
            double d = D2([&](double h1, double h2) {
                Eigen::VectorXd ix1 = Eigen::VectorXd::Zero(x.size());
                Eigen::VectorXd ix2 = Eigen::VectorXd::Zero(x.size());
                ix1[i] = h1;
                ix2[j] = h2;
                return (*this)(x + ix1 + ix2);
            });
            res(i, j) = d;
            if (i != j) {
                res(j, i) = d;
            }
        }
    }
    return res;
}

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

double Function::compute(const Eigen::VectorXd &x) const {
    return f(x);
}

Function::Function(BoxDomain box, std::function<double(const Eigen::VectorXd &)> f)
    : AbstractFunction(std::move(box)), f(std::move(f)) {}

Function::Function(BoxDomain box,
                   std::function<double(const Eigen::VectorXd &)> f,
                   std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad)
    : AbstractFunction(std::move(box)), f(std::move(f)), grad(std::move(grad)) {}

Function::Function(BoxDomain box,
                   std::function<double(const Eigen::VectorXd &)> f,
                   std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad,
                   std::function<Eigen::MatrixXd(const Eigen::VectorXd &)> hess)
    : AbstractFunction(std::move(box)), f(std::move(f)), grad(std::move(grad)), hess(std::move(hess)) {}

Eigen::VectorXd Function::compute_grad(const Eigen::VectorXd &x) const {
    if (grad) {
        return (*grad)(x);
    } else {
        return AbstractFunction::num_grad(x);
    }
}

Eigen::MatrixXd Function::compute_hess(const Eigen::VectorXd &x) const {
    if (grad) {
        return (*hess)(x);
    } else {
        return AbstractFunction::num_hess(x);
    }
}
