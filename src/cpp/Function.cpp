//
// Created by egorb on 10.10.2018.
//


#include "../Function.h"

Function::Function(BoxDomain domain) : domain(std::move(domain)) {}

const BoxDomain &Function::getDomain() const {
    return domain;
}

double Function::operator()(const Eigen::VectorXd &x) const {
    if (domain.inDomain(x)) {
        return compute(x);
    } else
        throw std::runtime_error("Out of bounds");
}
Eigen::VectorXd Function::gradient(const Eigen::VectorXd &x) {
    auto D = [](auto &&f) {
        double h = 0.01;
        auto t = (f(h) - f(-h)) / (2 * h);
        return t;
    };

    Eigen::VectorXd ans(this->domain.dim());
    for (size_t i = 0; i < x.size(); ++i) {
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

Rosenbrock::Rosenbrock(BoxDomain domain) : Function(std::move(domain)) {}


