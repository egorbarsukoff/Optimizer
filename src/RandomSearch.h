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
        Point<dim> new_point;
        if (CommonRandom::getB(p))
            new_point = Optimizer<dim>::f.getDomain().randomPoint();
        else
            new_point = (BoxDomain<dim>(Optimizer<dim>::track.back(),
                                   delta/sqrt(double(Optimizer<dim>::track.size()))) *
                                   Optimizer<dim>::f.getDomain()).randomPoint();
        if (Optimizer<dim>::f(new_point) < Optimizer<dim>::f(Optimizer<dim>::track.back())) {
            Optimizer<dim>::track.push_back(new_point);
            return;
        }
    }
public:
    //!
    //! \param f
    //! \param crits Критерий остановки
    //! \param h Размер окрестности
    //! \param p Вероятность выбора точки не из окрестности
    RandomSearch(const Function<dim>& f, const Criterion<dim>& crit, double h = 0.05, double p = 0.8) :
                    Optimizer<dim>(f, crit), p(p) {
        delta = pow(Optimizer<dim>::f.getDomain().measure(), 1./dim)*h;
    }
};


#endif //OPTIMIZER_RANDOMSEARCH_H
