//
// Created by eb on 09.10.2019.
//

#ifndef OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H
#define OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H

#include "Optimizer.h"
#include "LinearOptimizer.h"

class NewtonOptimizer : public Optimizer {
    LinearOptimizer linOpt = {std::unique_ptr<AbstractFunction>(nullptr), 0.05};
protected:
    void step() override;
    void reset() override;
public:
    NewtonOptimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit);
};

#endif //OPTIMIZER_OPTIM_INCLUDE_OPTIM_NEWTONOPTIMIZER_H
