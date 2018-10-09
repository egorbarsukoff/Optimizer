//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include "Vector.h"
#include "BoxDomain.h"
#include "Gradient.h"

//TODO: Сделать фабрику
//! @brief Класс абстрактной функции
//! @tparam Размерность функции
class Function {
protected:

    //! Область определения функции
    BoxDomain domain;

    //! Вычиление абстрактной функции в точке
    //! \param x Точка
    //! \return Результат
    virtual double compute(const Vector& x) const = 0;
public:
    Function (const BoxDomain& domain) : domain(domain) {}
    //! Возвращает область определения
    //! \return
    const BoxDomain &getDomain() const {
        return domain;
    }

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Vector &x) const {
        if (domain.inDomain(x)) {
            return compute(x);
        } else
            throw "Out of bounds"; //TODO сделать нормальное исключение
    }
};


//! Функция Розенброка
class Rosenbrock : public Function {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    double compute(const Vector& x) const override {
        return pow((1 - x[0]), 2) + 100 * pow((x[1] - pow(x[0], 2)), 2);
    }

public:

    Rosenbrock(const BoxDomain domain) : Function(domain) {}
};


#endif //OPTIMIZER_FUNCTION_H
