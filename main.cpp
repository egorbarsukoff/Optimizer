#include <iostream>

#include <optim/NewtonOptimizer.h>
#include "optim/Criterion.h"
#include "optim/RandomSearch.h"
#include "Functions.h"

#include "optim/Task.h"

int main(int argc, char *argv[]) {
    BoxDomain box2d{{{-2, 2}, {-2, 2}}};
    BoxDomain box3d{{{-2, 2}, {-2, 2}, {-2, 2}}};

    Task task;
    task.set_f<Rosenbrock>(std::move(box2d));
    task.add_crit<MaxN>(20);
    task.set_start(2, 1);
    auto[x, y] = task.start_and_reset<RandomSearch>();

    std::cout << x;

}