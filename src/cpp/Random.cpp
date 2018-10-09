//
// Created by egorb on 10.10.2018.
//

#include "../Random.h"

std::mt19937& Random::get_mt() {
    static std::mt19937 mt;
    return mt;
}

double Random::getU(double a, double b) {
    return std::uniform_real_distribution<double>(a, b)(Random::get_mt());
}

bool Random::getB(double p) {
    return std::bernoulli_distribution(p)(get_mt());
}