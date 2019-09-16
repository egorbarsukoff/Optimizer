#include <iostream>
#include <valarray>
#include "src/Gradient.h"
#include "src/Random.h"
#include "src/Criterion.h"
#include "src/RandomSearch.h"

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::valarray<T>& v) {
    stream << "{ ";
    for (auto& x: v) {
        stream << x << ' ';
    }
    stream << '}';
    return stream;
}

int main() {
    BoxDomain box({{-1, 1}, {-1, 1}});
    Rosenbrock f(box);
    std::valarray<double> start({1, 0});
    MaxN crit(100);
    NWithoutUpdates crit2(10000);
    FunctionChange crit3(0.0001);
    std::vector<Criterion*> t = {&crit, &crit2, &crit3};
    auto crits = CriterionPack(t);
    RandomSearch search(f, crit2);
    auto ans = search.optimize(start);

    for (auto& a : ans) {
        std::cout << a.x << " " << a.y << std::endl;
    }
    return 0;
}