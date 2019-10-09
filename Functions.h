//
// Created by eb on 09.10.2019.
//

#ifndef OPTIMIZER__FUNCTIONS_H
#define OPTIMIZER__FUNCTIONS_H

#include <Eigen/Core>
#include "optim/Function.h"

//! Функция Розенброка $[-2, 2]^2$
class Rosenbrock : public AbstractFunction {

protected:
    //! Вычиление функции в точке
    //! \param x Точка
    //! \return Результат
    [[nodiscard]] double compute(const Eigen::VectorXd &x) const override;
    Eigen::VectorXd compute_grad(const Eigen::VectorXd &x) const override;
    Eigen::MatrixXd compute_hess(const Eigen::VectorXd &x) const override;

public:

    explicit Rosenbrock(BoxDomain domain);

};

//! $x^2 + 3y^2 + 6z^2 + 2xy $
class SquareFunction : public AbstractFunction {

protected:
    [[nodiscard]] double compute(const Eigen::VectorXd &x) const override;
public:
    SquareFunction(BoxDomain domain);
};

#endif //OPTIMIZER__FUNCTIONS_H
