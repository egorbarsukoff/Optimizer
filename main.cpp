#include <iostream>
#include "src/Point.h"
#include "src/Gradient.h"
#include "src/CommonRandom.h"
#include "src/Criterion.h"
#include "src/RandomSearch.h"

int main() {
    BoxDomain<2> box({{{-5, 5}, {-5, 5}}});
    Rosenbrock f(box);
    Point<2> start(std::array<double, 2>({0, 0}));
    MaxN<2> crit(10);
    std::vector<Criterion<2>*> crits = {&crit};
    RandomSearch<2> search(f, crits);
    auto ans = search.optimize(start);
    for (auto& a : ans) {
        std::cout << a << " " << f(a) << std::endl;
    }
    return 0;
}