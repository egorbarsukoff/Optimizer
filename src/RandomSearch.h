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

    //! Вероятность, что точка будет выбираться из всего множества, а не из окрестности
    double p;

    //! Радиус окрестности
    double delta;

    //! Шаг оптимизатора
    void step() {
        Vector<dim> new_point;
        if (CommonRandom::getB(p))
            new_point = Optimizer<dim>::f.getDomain().randomPoint();
        else
            new_point = (BoxDomain<dim>(Optimizer<dim>::track.back().first,
                                   delta/sqrt(double(Optimizer<dim>::track.size()))) *
                                   Optimizer<dim>::f.getDomain()).randomPoint();
        double t;
        if ((t = Optimizer<dim>::f(new_point)) < Optimizer<dim>::f(Optimizer<dim>::track.back().first)) {
            Optimizer<dim>::track.emplace_back(new_point, t);
        }
    }
public:
    //!
    //! \param f
    //! \param crits Критерий остановки
    //! \param h Размер окрестности
    //! \param p Вероятность выбора точки не из окрестности
    RandomSearch(const Function<dim>& f, Criterion<dim>& crit, double h = 0.1, double p = 0.5) :
                    Optimizer<dim>(f, crit), p(p) {
        delta = pow(Optimizer<dim>::f.getDomain().measure(), 1./dim)*h;
    }
};


#endif //OPTIMIZER_RANDOMSEARCH_H
