#include <iostream>
#include "src/Vector.h"
#include "src/Gradient.h"
#include "src/CommonRandom.h"
#include "src/Criterion.h"
#include "src/RandomSearch.h"

int main() {
    BoxDomain box({{-1, 1}, {-1, 1}});
    Rosenbrock f(box);
    Vector start(std::vector<double>({1, 0}));
    MaxN crit(100);
    NWithoutUpdates crit2(10000);
    FunctionChange crit3(0.0001);
    auto crits = CriterionPack({&crit, &crit2});
    RandomSearch search(f, crit2);
    auto ans = search.optimize(start);

    for (auto& a : ans) {
        std::cout << a.first << " " << a.second << std::endl;
    }
    return 0;
}