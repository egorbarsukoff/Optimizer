//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <cmath>
#include <memory>
#include <Eigen/Core>
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
    [[nodiscard]] virtual double compute(const Eigen::VectorXd &x) const = 0;

public:
    explicit Function(BoxDomain domain);
    //! Возвращает область определения
    //! \return
    [[nodiscard]] const BoxDomain &getDomain() const;


    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Eigen::VectorXd &x) const;

    Eigen::VectorXd gradient(const Eigen::VectorXd &x);
};


//! Функция Розенброка
class Rosenbrock : public Function {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] double compute(const Eigen::VectorXd &x) const override;

public:

    explicit Rosenbrock(BoxDomain domain);

};


#endif //OPTIMIZER_FUNCTION_H
