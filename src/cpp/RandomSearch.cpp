//
// Created by egorb on 10.10.2018.
//

#include "../RandomSearch.h"

void RandomSearch::step() {
    Vector new_point(track.back().first.getDim());
    if (Random::getB(p))
        new_point = Optimizer::f->getDomain().randomPoint();
    else
        new_point = (BoxDomain(Optimizer::track.back().first,
                               delta / sqrt(double(Optimizer::track.size()))) *
                     //TODO: правильное уменьшиние окрестности
                     Optimizer::f->getDomain()).randomPoint();
    double t;
    if ((t = (*f)(new_point)) < (*f)(Optimizer::track.back().first)) {
        Optimizer::track.emplace_back(new_point, t);

    }
}

RandomSearch::RandomSearch(const Function& f, Criterion& crit, double h, double p) :
        Optimizer(f, crit), p(p) {
    delta = pow(Optimizer::f->getDomain().measure(), 1./2)*h; //TODO: нормальная степень
}
