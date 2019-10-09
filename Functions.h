//
// Created by eb on 09.10.2019.
//

#ifndef OPTIMIZER__FUNCTIONS_H
#define OPTIMIZER__FUNCTIONS_H

#include <Eigen/Core>
#include "optim/Function.h"

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

#endif //OPTIMIZER__FUNCTIONS_H
