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
//! Точками кастомизации являются методы compute, compute_grad и compute_hess
//! compute - сама функция, переопредлять обязательно
//! compute_grad - градиент, если не переопределять, вычисляется численно
//! compute_hess - матрица Гессе, если не переопределять, вычисляется численно
class AbstractFunction {
protected:

    //! Область определения функции
    BoxDomain domain;

    //! Вычиление абстрактной функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] virtual double compute(const Eigen::VectorXd &x) const = 0;

    //! Вычесление градиента
    //! Если не переопределена в наследнике, то вычисляется численно
    //! \param x точка, в которой будет вычислен градиент
    //! \return градиент функции
    [[nodiscard]] virtual Eigen::VectorXd compute_grad(const Eigen::VectorXd &x) const;

    //! Вычесление матрицы Гессе
    //! Если не переопределена в наследнике, то вычисляется численно
    //! \param x точка, в которой будет вычислена матрицы
    //! \return матрицы Гессе функции
    [[nodiscard]] virtual Eigen::MatrixXd compute_hess(const Eigen::VectorXd &x) const;

    //! Численное вычисление матрицы Гессе
    //! \param x Точка, в которой будет вычеслена матрица
    //! \return матрица Гессе
    [[nodiscard]] Eigen::MatrixXd num_hess(const Eigen::VectorXd &x) const;

    //! Численное вычисление градиента
    //! \param x Точка, в которой будет вычеслен градиент
    //! \return градиент функции
    [[nodiscard]] Eigen::VectorXd num_grad(const Eigen::VectorXd &x) const;

    //! Проверяет, что x лежит в области определении функции this и вызывает f(x) для данного f
    //! \param f Функция, принимающая Eigen::VectorXd
    //! \param x точка, в которой будет вычеслен f(x)
    //! \return результат f(x)
    //! \throws std::runtime_error("Out of bounds")
    template<typename T>
    decltype(auto) checkBoxAndCall(T &&f, const Eigen::VectorXd &x) const {
        if (domain.inDomain(x)) {
            return f(x);
        } else
            throw std::runtime_error("Out of bounds");
    }

public:

    //! Конструктор
    //! \param domain область определения
    explicit AbstractFunction(BoxDomain domain);

    //! Возвращает область определения
    //! \return
    [[nodiscard]] const BoxDomain &getDomain() const;

    void setDomain(BoxDomain domain);

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Eigen::VectorXd &x) const;

    //! Вычисление градиента в точке $x$
    //! Вычислится численно или аналитически в зависимотcи от того, переопределена ли compute_grad
    //! \param x Точка в которой вычисляется градиент
    //! \return Градиент
    [[nodiscard]] Eigen::VectorXd gradient(const Eigen::VectorXd &x) const;

    //! Вычисление матрицы Гессе в точке $x$
    //! Вычислится численно или аналитически в зависимоcти от того, переопределена ли compute_hess
    //! \param x Точка в которой вычисляется градиент
    //! \return Гессиан
    [[nodiscard]] Eigen::MatrixXd hessian(const Eigen::VectorXd &x) const;
};

//! @brief Функция определенная любыми callable объектами
//! Если не определены градиент/матрица Гессе, они вычисляются численно
class Function : public AbstractFunction {
    std::function<double(const Eigen::VectorXd &)> f;
    std::optional<std::function<Eigen::VectorXd(const Eigen::VectorXd &)>> grad;
    std::optional<std::function<Eigen::MatrixXd(const Eigen::VectorXd &)>> hess;

protected:
    [[nodiscard]] double compute(const Eigen::VectorXd &x) const override;
    [[nodiscard]] Eigen::VectorXd compute_grad(const Eigen::VectorXd &x) const override;
    [[nodiscard]] Eigen::MatrixXd compute_hess(const Eigen::VectorXd &x) const override;
public:
    Function(BoxDomain box, std::function<double(const Eigen::VectorXd &)> f);
    Function(BoxDomain box,
             std::function<double(const Eigen::VectorXd &)> f,
             std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad);
    Function(BoxDomain box,
             std::function<double(const Eigen::VectorXd &)> f,
             std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad,
             std::function<Eigen::MatrixXd(const Eigen::VectorXd &)> hess);
};



#endif //OPTIMIZER_FUNCTION_H
