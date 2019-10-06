//
// Created by egorb on 10.10.2018.
//

#include "../RandomSearch.h"

void RandomSearch::step() {
    std::valarray<double> new_point(track.back().x.size());
    if (Random::getB(p))
        new_point = Optimizer::f->getDomain().randomPoint();
    else
        new_point = (BoxDomain(Optimizer::track.back().x,
                               delta / sqrt(double(Optimizer::track.size()))) *
                     //TODO: правильное уменьшиние окрестности
                     Optimizer::f->getDomain()).randomPoint();
    double t;
    if ((t = (*f)(new_point)) < (*f)(Optimizer::track.back().x)) {
        Optimizer::track.emplace_back(std::move(new_point), t);

    }
}

RandomSearch::RandomSearch(std::unique_ptr<Function> f, std::unique_ptr<Criterion> crit, double h, double p) :
    Optimizer(std::move(f), std::move(crit)), p(p) {
    delta = pow(Optimizer::f->getDomain().measure(), 1./2)*h; //TODO: нормальная степень
}
