//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H


#include "Point.h"

template <size_t dim>
class BoxDomain {
public:
    bool inDomain(const Point<dim>& p) const {
        return true;
    };
    BoxDomain<dim> intersect(const BoxDomain<dim>& d);
};


#endif //OPTIMIZER_DOMAIN_H
