#include <iostream>
#include "src/Point.h"
#include "src/Gradient.h"
#include "src/CommonRandom.h"
#include "src/Criterion.h"
#include "src/RandomSearch.h"

int main() {
    BoxDomain<2> box({{{-5, 5}, {-5, 5}}});
    Rosenbrock f(box);
    Point<2> start(std::array<double, 2>({50, 50}));
    MaxN<2> crit(100);
    NWithoutUpdates<2> crit2(10000);
    auto crits = CriterionPack<2>({&crit, &crit2});
    RandomSearch<2> search(f, crits);
    auto ans = search.optimize(start);

    for (auto& a : ans) {
        std::cout << a << " " << f(a) << std::endl;
    }
    return 0;
}