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
    auto D = [](auto &&f) {
        double h = 0.01;
        auto t = (f(h) - f(-h)) / (2 * h);
        return t;
    };

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

double Rosenbrock::compute(const Eigen::VectorXd &x) const {
    return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
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
