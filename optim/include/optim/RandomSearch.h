//
// Created by egorb on 22.09.2018.
//

#ifndef OPTIMIZER_RANDOMSEARCH_H
#define OPTIMIZER_RANDOMSEARCH_H


#include <cstddef>
#include <random>
#include "Optimizer.h"


//! @brief Оптимизация методом случайного поиска
class RandomSearch : public Optimizer {

    //! Вероятность, что точка будет выбираться из всего множества, а не из окрестности
    double p;

    //! Радиус окрестности
    double delta;

    //! Шаг оптимизатора
    bool step() override;

public:
    //!
    //! \param f
    //! \param crits Критерий остановки
    //! \param h Размер окрестности
    //! \param p Вероятность выбора точки не из окрестности
    RandomSearch(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit, double h = 0.1, double p = 0.5);
};


#endif //OPTIMIZER_RANDOMSEARCH_H
