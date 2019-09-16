//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_GRADIENT_H
#define OPTIMIZER_GRADIENT_H

#include <functional>
#include <iostream>
#include "valarray"
#include "Function.h"


//! @brief Градиент функции в точке
class Gradient : public std::valarray<double>{

    //! Точка, в которой был вычиллен градиаент
    std::valarray<double> from;

    //! Вычисление производной одномерной функции в точке 0
    //! \param f Одномерная функция
    //! \return Резульат
    static double D(const std::function<double(double)> &f);
public:

    //! Вычисление градиента
    //! \param f Функция
    //! \param p Точка, в которой будет вычисляться градиент
    explicit Gradient(const Function& f, const std::valarray<double>& p);

};


#endif //OPTIMIZER_GRADIENT_H
