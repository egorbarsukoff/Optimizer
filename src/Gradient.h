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
//! \tparam dim Размерность
template <size_t dim>
class Gradient : public Vector<dim>{

    //! Точка, в которой был вычиллен градиаент
    const Vector<dim>& from;

    //! Вычисление производной одномерной функции в точке 0
    //! \param f Одномерная функция
    //! \return Резульат
    static double D(auto&& f) {
        double h = 0.01;
        auto t = (f(h) - f(-h)) / (2*h);
        return t;
    }
public:

    //! Вычисление градиента
    //! \param f Функция
    //! \param p Точка, в которой будет вычисляться градиент
    explicit Gradient<dim>(const Function<dim>& f, const Vector<dim>& p) : from(p) {
        for (size_t i = 0; i < from.getX().size(); ++i) {
            this->x[i] = D([&](double h) {
                return f(p + Vector<dim>(i)*h);
            });
        }
    }

};


#endif //OPTIMIZER_GRADIENT_H
