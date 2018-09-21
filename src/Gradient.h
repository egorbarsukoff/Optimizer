//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_GRADIENT_H
#define OPTIMIZER_GRADIENT_H

#include "Point.h"

template <size_t dim>
class Gradient : public Point<dim>{
    Point<dim> from;
};


#endif //OPTIMIZER_GRADIENT_H
