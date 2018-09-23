//
// Created by egorb on 22.09.2018.
//

#ifndef OPTIMIZER_RANDOMSEARCH_H
#define OPTIMIZER_RANDOMSEARCH_H


#include <cstddef>
#include <random>
#include "Optimizer.h"


//! @brief Оптимизация методом случайного поиска
//! \tparam dim Размерность
template <size_t dim>
class RandomSearch : public Optimizer<dim> {
    double h;
    double p;
    double delta;
    void step() {
        Point<dim> new_point;
        while (true) {
            if (CommonRandom::getB(p))
                new_point = Optimizer<dim>::f.getDomain().randomPoint();
            else
                Point<dim> new_point = BoxDomain(Optimizer<dim>::track.back(), delta) *
                                       Optimizer<dim>::f.getDomain();
            if (f(new_point) < f(Optimizer<dim>::track.back())) {
                Optimizer<dim>::track.push_back(new_point);
                return;
            }
        }
    }
public:
    RandomSearch(const Function<dim>& f, const Criterion<dim>& crit, double h = 0.1, double p = 0.5) :
                    Optimizer<dim>(f, crit), h(h), p(p) {
        delta = pow(f.getDomain().measure(), 1./dim)/10;
    }
};


#endif //OPTIMIZER_RANDOMSEARCH_H
