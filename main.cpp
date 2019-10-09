#include <iostream>
#include "optim/LinearOptimizer.h"
#include "optim/Criterion.h"
#include "optim/RandomSearch.h"


int main() {
    BoxDomain box{{{-2, 2}, {-2, 2}}};
    auto r = std::make_unique<Rosenbrock>(std::move(box));
    std::vector<double> c;
    for (int i = 0; i < 20000; i += 1) {
        auto x = r->getDomain().randomPoint();
        c.push_back((r->gradient(x) - r->num_grad(x)).maxCoeff());
    }
    std::cout << *std::max_element(c.begin(), c.end());
    //    auto f = std::make_unique<Function>(box,[](auto x) {
    //        return cos(x[0]);
    //    });
    //    auto ans = LinearOptimizer(std::move(f), 0.1).optimize(Eigen::VectorXd::Zero(1));
    //
    //    for (auto& a : ans) {
    //        std::cout << a.x << " ";
    //    }
}