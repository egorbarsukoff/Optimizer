//
// Created by egorb on 10.10.2018.
//

#include "../Function.h"

Function::Function (const BoxDomain& domain) : domain(domain) {}

const BoxDomain &Function::getDomain() const {
    return domain;
}

double Function::operator()(const Vector &x) const {
    if (domain.inDomain(x)) {
        return compute(x);
    } else
        throw "Out of bounds"; //TODO сделать нормальное исключение
}

double Rosenbrock::compute(const Vector& x) const {
    return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
}

Rosenbrock::Rosenbrock(const BoxDomain domain) : Function(domain) {}