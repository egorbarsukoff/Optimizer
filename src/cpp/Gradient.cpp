//
// Created by egorb on 10.10.2018.
//

#include "../Gradient.h"

double Gradient::D(const std::function<double(double)> &f) {
    double h = 0.01;
    auto t = (f(h) - f(-h)) / (2*h);
    return t;
}

Gradient::Gradient(const Function &f, const std::valarray<double> &p) : std::valarray<double>(p.size()), from(p) {
    for (size_t i = 0; i < from.size(); ++i) {
        static_cast<std::valarray<double>&>(*this)[i] = D([&](double h) {
            auto ix = std::valarray<double>(i);
            ix[i] = 1;
            return f(p + ix*h);
        });
    }
}

