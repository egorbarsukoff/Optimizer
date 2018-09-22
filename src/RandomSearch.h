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

};


#endif //OPTIMIZER_RANDOMSEARCH_H
