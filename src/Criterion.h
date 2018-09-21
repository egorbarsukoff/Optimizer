//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include <initializer_list>
#include "Point.h"

template <size_t n>
class Criterion {
public:
    virtual bool operator() (const Track<n>& track) const = 0 ;
};


#endif //OPTIMIZER_CRITERION_H
