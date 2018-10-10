//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include "Vector.h"
#include "BoxDomain.h"

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
    Function (const BoxDomain& domain);
    //! Возвращает область определения
    //! \return
    const BoxDomain &getDomain() const;

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Vector &x) const;
};


//! Функция Розенброка
class Rosenbrock : public Function {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    double compute(const Vector& x) const override;

public:

    Rosenbrock(const BoxDomain domain);
};


#endif //OPTIMIZER_FUNCTION_H
