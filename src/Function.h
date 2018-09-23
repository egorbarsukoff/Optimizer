//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include "Point.h"
#include "BoxDomain.h"
#include "Gradient.h"


//! @brief Класс абстрактной функции
//! @tparam Размерность функции
template <size_t dim>
class Function {
protected:

    //! Область определения функции
    BoxDomain<dim> domain;

    //! Вычиление абстрактной функции в точке
    //! \param x Точка
    //! \return Результат
    virtual double compute(const Point<dim>& x) const = 0;
public:

    //! Возвращает область определения
    //! \return
    const BoxDomain<dim> &getDomain() const {
        return domain;
    }

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Point<dim> &x) const {
        if (domain.inDomain(x)) {
            return compute(x);
        } else
            throw "Out of bounds";
    }
};


//! Функция Розенброка
class Rosenbrock : public Function<2> {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    double compute(const Point<2>& x) const override {
        return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
    }
};


#endif //OPTIMIZER_FUNCTION_H
