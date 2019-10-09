//
// Created by egorb on 10.10.2018.
//


#include <iostream>
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
    static auto D = [](auto &&f, int mode) {
        /* modes:
         * 0 - not on bounds
         * 1 - left bound
         * 2 - right bound
         */
        double h = 0.1e-5;
        switch (mode) {
        case 0:return (f(h) - f(-h)) / (2 * h);
        case 1:return (f(h) - f(0)) / (h);
        case 2:return (f(0) - f(-h)) / (h);
        default:assert(false);
        }
    };
    Eigen::VectorXd ans(this->domain.dim());
    for (size_t i = 0; i < static_cast<size_t>(x.size()); ++i) {
        for (int mode = 0; mode < 3; ++mode) {
            try {
                ans[i] = D([&](double h) {
                    Eigen::VectorXd ix = Eigen::VectorXd::Zero(x.size());
                    ix[i] = 1;
                    return (*this)(x + ix * h);
                }, mode);
            } catch (std::runtime_error &e) {
                if (i != 2)
                    continue;
                else
                    throw;
            }
            break;
        }

    }
    return ans;
}

Eigen::MatrixXd AbstractFunction::num_hess(const Eigen::VectorXd &x) const {
    static auto D2 = [](auto &&f, int mode) {
        /* modes:
         * 0 - not on bounds
         * 1 - left bound
         * 2 - right bound
         * 3 - upper bound
         * 4 - lower bound
         * 5 - upper left corner
         * 6 - upper right corner
         * 7 - lower left corner
         * 8 - lower right corner
         * */
        double h = 1e-5;
        switch (mode) {
        case 0:return (f(h, h) - f(-h, h) - f(h, -h) + f(-h, -h)) / (4 * h * h);
        case 1:return (f(h, h) - f(0, h) - f(h, -h) + f(0, -h)) / (2 * h * h);
        case 2:return (f(0, h) - f(-h, h) - f(0, -h) + f(-h, -h)) / (2 * h * h);
        case 3:return (f(h, 0) - f(-h, 0) - f(h, -h) + f(-h, -h)) / (2 * h * h);
        case 4:return (f(h, h) - f(-h, h) - f(h, 0) + f(-h, 0)) / (2 * h * h);
        case 5:return (f(h, 0) - f(0, 0) - f(h, -h) + f(0, -h)) / (h * h);
        case 6:return (f(0, 0) - f(-h, 0) - f(0, -h) + f(-h, -h)) / (h * h);
        case 7:return (f(h, h) - f(0, h) - f(h, 0) + f(0, 0)) / (h * h);
        case 8:return (f(0, h) - f(-h, h) - f(0, 0) + f(0, -h)) / (h * h);
        default:assert(false);
        }
    };
    Eigen::MatrixXd res(x.size(), x.size());
    for (long int i = 0; i < x.size(); ++i) {
        for (long int j = 0; j <= i; ++j) {
            for (int mode = 0; mode < 9; ++mode) { // try to calculate all possible num formulas
                try {
                    double d = D2([&](double h1, double h2) {
                        Eigen::VectorXd ix1 = Eigen::VectorXd::Zero(x.size());
                        Eigen::VectorXd ix2 = Eigen::VectorXd::Zero(x.size());
                        ix1[i] = h1;
                        ix2[j] = h2;
                        return (*this)(x + ix1 + ix2);
                    }, mode);
                    res(i, j) = d;
                    if (i != j) {
                        res(j, i) = d;
                    }
                } catch (std::runtime_error &e) {
                    if (mode != 8)
                        continue;
                    else {
                        std::cout << x << "\n\n";
                        throw;
                    }
                }
                break;
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
