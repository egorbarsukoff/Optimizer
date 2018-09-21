//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include <initializer_list>
#include "Point.h"

class Criterion {
public:
    virtual bool operator() (const Track& track) = 0;
};


#endif //OPTIMIZER_CRITERION_H
