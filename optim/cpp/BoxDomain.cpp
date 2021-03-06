//
// Created by egorb on 10.10.2018.
//

#include <iostream>
#include "optim/BoxDomain.h"

BoxDomain::BoxDomain (std::vector<std::array<double, 2>> _bounds) : bounds(std::move(_bounds)) {
    for (const std::array<double, 2>& b: bounds) {
        if (b[0] >= b[1] - 1e-12)
            throw std::runtime_error("Bad bounds");
    }
}

BoxDomain::BoxDomain(const Eigen::VectorXd &p, double eps) : bounds(p.size()) {
    eps = std::clamp<double>(eps, 1e-5, 1000000);
    for (size_t i = 0; i < static_cast<size_t>(p.size()); ++i) {
        bounds[i][0] = p[i] - eps;
        bounds[i][1] = p[i] + eps;
    }
}

bool BoxDomain::inDomain(const Eigen::VectorXd &p) const {
    assert(static_cast<size_t>(p.size()) == bounds.size());
    for (size_t i = 0; i < static_cast<size_t>(p.size()); ++i) {
        if (bounds[i][0] > p[i] + 1e-8 || bounds[i][1] < p[i] - 1e-8)
            return false;
    }
    return true;
}

double BoxDomain::measure() const {
    double res = 1;
    for (auto& bound : bounds) {
        res *= bound[1] - bound[0];
    }
    return res;
}

Eigen::VectorXd BoxDomain::randomPoint() const {
    Eigen::VectorXd p(bounds.size());
    for (size_t i = 0; i < static_cast<size_t>(p.size()); ++i) {
        p[i] = Random::getU(bounds[i][0], bounds[i][1]);
    }
    return p;
}

BoxDomain operator*(const BoxDomain& a, const BoxDomain& b) {
    std::vector<std::array<double, 2>> new_box(a.bounds.size());
    for (size_t i = 0; i < new_box.size(); ++i) {
        new_box[i][0] = std::max(a.bounds[i][0], b.bounds[i][0]);
        new_box[i][1] = std::min(a.bounds[i][1], b.bounds[i][1]);
        assert(new_box[i][0] <= new_box[i][1]);
    }
    return BoxDomain(new_box);
}
size_t BoxDomain::dim() const {
    return bounds.size();
}

double BoxDomain::intersectCoeff(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const {
    assert(x.size() == p.size());
    assert(inDomain(x));
    auto max_coef = std::numeric_limits<double>::max();
    for (int i = 0; i < p.size(); ++i) {
        if (abs(p[i]) < 1e-8) {
            continue;
        }
        double bound = (p[i] > 0 ? bounds[i][1] : bounds[i][0]) - x[i];
        max_coef = std::min(max_coef, bound / p[i]);
    }
    if (max_coef == std::numeric_limits<double>::max()) {
        throw std::runtime_error("zero p");
    }
    return max_coef;
}
const std::array<double, 2> &BoxDomain::operator[](size_t i) const {
    return bounds[i];
}
