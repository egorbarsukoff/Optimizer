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
    double p;
    double delta;
    void step() {
        Point<dim> new_point;
        while (true) {
            if (CommonRandom::getB(p))
                new_point = Optimizer<dim>::f.getDomain().randomPoint();
            else
                new_point = (BoxDomain<dim>(Optimizer<dim>::track.back(), delta) *
                                       Optimizer<dim>::f.getDomain()).randomPoint();
            if (Optimizer<dim>::f(new_point) < Optimizer<dim>::f(Optimizer<dim>::track.back())) {
                Optimizer<dim>::track.push_back(new_point);
                return;
            }
        }
    }
public:
    RandomSearch(const Function<dim>& f, std::vector<Criterion<dim>*>& crits, double h = 0.05, double p = 0.2) :
                    Optimizer<dim>(f, crits), p(p) {
        delta = pow(Optimizer<dim>::f.getDomain().measure(), 1./dim)*h;
    }
};


#endif //OPTIMIZER_RANDOMSEARCH_H
