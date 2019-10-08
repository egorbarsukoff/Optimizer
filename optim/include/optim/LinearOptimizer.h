//
// Created by egor on 10/7/19.
//

#ifndef OPTIMIZER_SRC_LINIAROPTIMIZER_H
#define OPTIMIZER_SRC_LINIAROPTIMIZER_H

#include "Optimizer.h"

//! @brief Нахождение конца промежутка монотонного убывания функции на $[x, b]$, где $b$ - конец области определения $f$
class LinearOptimizer : public Optimizer {
    //! Начальный шаг сетки
    Eigen::VectorXd init_step_size;

    //! Текущий шаг сетки
    Eigen::VectorXd step_size;
public:
    //! Конструктор
    //! @param f  оптимизируемая функция
    //! @param step начальный шаг сетки
    LinearOptimizer(std::unique_ptr<AbstractFunction> f, double step);
protected:
    //! Шаг оптимизатора
    void step() override;

    //! Сброс оптимизатора
    void reset() override;
};

#endif //OPTIMIZER_SRC_LINIAROPTIMIZER_H
