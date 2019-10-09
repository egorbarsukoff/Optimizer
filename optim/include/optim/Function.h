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
class AbstractFunction {
protected:

    //! Область определения функции
    BoxDomain domain;

    //! Вычиление абстрактной функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] virtual double compute(const Eigen::VectorXd &x) const = 0;
    [[nodiscard]] virtual Eigen::VectorXd compute_grad(const Eigen::VectorXd &x) const;
    [[nodiscard]] virtual Eigen::MatrixXd compute_hess(const Eigen::VectorXd &x) const;

    [[nodiscard]] Eigen::MatrixXd num_hess(const Eigen::VectorXd &x) const;
    template<typename T>
    decltype(auto) checkBoxAndCall(T &&f, const Eigen::VectorXd &x) const {
        if (domain.inDomain(x)) {
            return f(x);
        } else
            throw std::runtime_error("Out of bounds");
    }

public:

    [[nodiscard]] Eigen::VectorXd num_grad(const Eigen::VectorXd &x) const;
    explicit AbstractFunction(BoxDomain domain);
    //! Возвращает область определения
    //! \return
    [[nodiscard]] const BoxDomain &getDomain() const;

    //! Вызов вычисления функции
    //! \param x Точка в которой вычисляется функция
    //! \return Результат
    double operator()(const Eigen::VectorXd &x) const;

    //! Вычисление градиента в точке $x$
    //! \param x Точка в которой вычисляется градиент
    //! \return Градиент
    [[nodiscard]] Eigen::VectorXd gradient(const Eigen::VectorXd &x) const;

    //! Вычисление матрицы Гессе в точке $x$
    //! \param x Точка в которой вычисляется градиент
    //! \return Гессиан
    [[nodiscard]] Eigen::MatrixXd hessian(const Eigen::VectorXd &x) const;
};

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

//! Функция Розенброка
class Rosenbrock : public AbstractFunction {

    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] double compute(const Eigen::VectorXd &x) const override;
protected:
    Eigen::VectorXd compute_grad(const Eigen::VectorXd &x) const override;
    Eigen::MatrixXd compute_hess(const Eigen::VectorXd &x) const override;

public:

    explicit Rosenbrock(BoxDomain domain);

};

#endif //OPTIMIZER_FUNCTION_H
