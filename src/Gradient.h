//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_GRADIENT_H
#define OPTIMIZER_GRADIENT_H

#include <functional>
#include <iostream>
#include "Vector.h"
#include "Function.h"


//! @brief Градиент функции в точке
class Gradient : public Vector{

    //! Точка, в которой был вычиллен градиаент
    const Vector& from;

    //! Вычисление производной одномерной функции в точке 0
    //! \param f Одномерная функция
    //! \return Резульат
    static double D(std::function<double(double)> f);
public:

    //! Вычисление градиента
    //! \param f Функция
    //! \param p Точка, в которой будет вычисляться градиент
    explicit Gradient(const Function& f, const Vector& p);

};


#endif //OPTIMIZER_GRADIENT_H
