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
    [[nodiscard]] virtual double compute(const std::valarray<double> &x) const = 0;

public:
    explicit Function(BoxDomain domain);
    //! Возвращает область определения
    //! \return
    [[nodiscard]] const BoxDomain &getDomain() const;


    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const std::valarray<double> &x) const;

    std::valarray<double> gradient(const std::valarray<double> &x);
};


//! Функция Розенброка
class Rosenbrock : public Function {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] double compute(const std::valarray<double> &x) const override;

public:

    explicit Rosenbrock(BoxDomain domain);

    [[nodiscard]] static std::unique_ptr<Function> create(BoxDomain box);
};


#endif //OPTIMIZER_FUNCTION_H
