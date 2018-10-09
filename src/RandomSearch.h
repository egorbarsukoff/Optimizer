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
class RandomSearch : public Optimizer {

    //! Вероятность, что точка будет выбираться из всего множества, а не из окрестности
    double p;

    //! Радиус окрестности
    double delta;

    //! Шаг оптимизатора
    void step() {
        Vector new_point(track.back().first.getDim());
        if (CommonRandom::getB(p))
            new_point = Optimizer::f.getDomain().randomPoint();
        else
            new_point = (BoxDomain(Optimizer::track.back().first,
                                   delta/sqrt(double(Optimizer::track.size()))) * //TODO: правильное уменьшиние окрестности
                                   Optimizer::f.getDomain()).randomPoint();
        double t;
        if ((t = Optimizer::f(new_point)) < Optimizer::f(Optimizer::track.back().first)) {
            Optimizer::track.emplace_back(new_point, t);
        }
    }
public:
    //!
    //! \param f
    //! \param crits Критерий остановки
    //! \param h Размер окрестности
    //! \param p Вероятность выбора точки не из окрестности
    RandomSearch(const Function& f, Criterion& crit, double h = 0.1, double p = 0.5) :
                    Optimizer(f, crit), p(p) {
        delta = pow(Optimizer::f.getDomain().measure(), 1./2)*h; //TODO: нормальная степень
    }
};


#endif //OPTIMIZER_RANDOMSEARCH_H
