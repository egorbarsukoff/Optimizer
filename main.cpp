#include <iostream>

#include <optim/NewtonOptimizer.h>
#include "optim/Criterion.h"
#include "optim/RandomSearch.h"
#include "Functions.h"

#include "optim/Task.h"


int main() {
    BoxDomain box{{{-2, 2}, {-2, 2}}};

    Task task;
    task.set_f<Rosenbrock>(box);
    task.add_crit<MaxN>(10);
    task.set_start(0, 0);
    auto[x, y] = task.start_and_reset<NewtonOptimizer>();

    std::cout << x;

}