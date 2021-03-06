//
// Created by eb on 09.10.2019.
//

#ifndef OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H
#define OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H

#include "Optimizer.h"
#include "LinearOptimizer.h"

//! @brief Оптимизатор Ньютона
class NewtonOptimizer : public Optimizer {
    LinearOptimizer linOpt = {std::unique_ptr<AbstractFunction>(nullptr), std::unique_ptr<Criterion>(nullptr), 0.05};
protected:
    bool step() override;
    void reset() override;
public:
    //! Конструктор
    //! @param f оптимизируемая функция
    //! @param crit Критерий остановки
    NewtonOptimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit);
};

#endif //OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H
