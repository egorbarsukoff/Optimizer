//
// Created by egorb on 10.10.2018.
//

#include "../BoxDomain.h"

BoxDomain::BoxDomain (std::vector<std::array<double, 2>> _bounds) : bounds(std::move(_bounds)) {
    for (const std::array<double, 2>& b: bounds) {
        if (b[0] >= b[1])
            throw "Bad bounds"; //TODO: Сделать нормальное исключение
    }
}

BoxDomain::BoxDomain (Vector p, double eps) : bounds(p.getDim()) {
    for (size_t i = 0; i < p.getDim(); ++i) {
        bounds[i][0] = p[i] - eps;
        bounds[i][1] = p[i] + eps;
    }
}

bool BoxDomain::inDomain(const Vector& p) const {
    for (int i = 0; i < p.getDim(); ++i) {
        if (bounds[i][0] > p[i] || bounds[i][1] < p[i])
            return false;
    }
    return true;
}

double BoxDomain::measure() const {
    double res = 1;
    for (int i = 0; i < bounds.size(); ++i) {
        res *= bounds[i][1] - bounds[i][0];
    }
    return res;
}

Vector BoxDomain::randomPoint() const {
    Vector p(bounds.size());
    for (size_t i = 0; i < p.getDim(); ++i) {
        p[i] = Random::getU(bounds[i][0], bounds[i][1]);
    }
    return p;
}

BoxDomain operator*(const BoxDomain& a, const BoxDomain& b) {
    std::vector<std::array<double, 2>> new_box(a.bounds.size());
    for (size_t i = 0; i < new_box.size(); ++i) {
        new_box[i][0] = std::max(a.bounds[i][0], b.bounds[i][0]);
        new_box[i][1] = std::min(a.bounds[i][1], b.bounds[i][1]);
        assert(new_box[i][0] < new_box[i][1]);
    }
    return BoxDomain(new_box);
}