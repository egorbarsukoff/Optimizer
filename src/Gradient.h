//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_GRADIENT_H
#define OPTIMIZER_GRADIENT_H

#include <functional>
#include <iostream>
#include "Point.h"
#include "Function.h"


//! @brief Градиент функции в точке
//! \tparam dim Размерность
template <size_t dim>
class Gradient : public Point<dim>{
    //! Точка, в которой был вычиллен градиаент
    const Point<dim>& from;
    //! Вычисление производной одномерной функции в точке 0
    //! \param f Одномерная функция
    //! \return Резульат
    double D(auto&& f) {
        double h = 0.01;
        return (f(h) - f(-h)) / (2*h);
    }
public:
    //! Вычисление градиента
    //! \param f Функция
    //! \param p Точка, в которой будет вычисляться градиент
    explicit Gradient<dim>(const Function<dim>& f, const Point<dim>& p) : from(p) {
        for (size_t i = 0; i < from.getX().size(); ++i) {
            this->x[i] = D([&](double h) {
                return f(p + Point<dim>(i)*h);
            });
        }
        for (auto a: Point<dim>::x) {
            std::cout << a << std::endl;
        }
    }

};


#endif //OPTIMIZER_GRADIENT_H
