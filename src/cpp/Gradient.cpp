//
// Created by egorb on 10.10.2018.
//

#include "../Gradient.h"

double Gradient::D(std::function<double(double)> f) {
    double h = 0.01;
    auto t = (f(h) - f(-h)) / (2*h);
    return t;
}

Gradient::Gradient(const Function &f, const Vector &p) : Vector(p.getDim()), from(p) {
    for (size_t i = 0; i < from.getX().size(); ++i) {
        this->x[i] = D([&](double h) {
            return f(p + Vector(i)*h);
        });
    }
}

