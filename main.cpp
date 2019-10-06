#include <iostream>
#include <valarray>
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
    std::valarray<double> start({1, 0});
    auto crit = NWithoutUpdates::create(1000);
    auto crit2 = MaxN::create(100);
    //    auto comp = CriterionPack::create();
    //    RandomSearch search(f, std::move(comp));
    std::vector<std::unique_ptr<Criterion>> aa;
    aa.push_back(std::move(crit));
    auto a = CriterionPack::create(std::move(aa));
    RandomSearch search(Rosenbrock::create(box), std::move(a));
    auto ans = search.optimize(start);

    for (auto& a : ans) {
        std::cout << a.x << " " << a.y << std::endl;
    }
    return 0;
}