//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <tuple>

class Function {
public:
    template <typename... Args>
    virtual double operator() (std::tuple<Args...>) = 0;
};


#endif //OPTIMIZER_FUNCTION_H
