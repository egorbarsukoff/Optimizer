//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include <memory>
#include <valarray>
#include "BoxDomain.h"


//! @brief Класс абстрактной функции
//! @tparam Размерность функции
class Function {
protected:

    //! Область определения функции
    BoxDomain domain;

    //! Вычиление абстрактной функции в точке
    //! \param x Точка
    //! \return Результат
    virtual double compute(const std::valarray<double>& x) const = 0;

public:
    Function (const BoxDomain& domain);
    //! Возвращает область определения
    //! \return
    const BoxDomain &getDomain() const;

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const std::valarray<double> &x) const;

    virtual std::shared_ptr<Function> copy() const = 0;
};


//! Функция Розенброка
class Rosenbrock : public Function {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    double compute(const std::valarray<double>& x) const override;

public:

    explicit Rosenbrock(const BoxDomain domain);

    std::shared_ptr<Function> copy() const override;
};


#endif //OPTIMIZER_FUNCTION_H
