//
// Created by egorb on 27.09.2018.
//

#ifndef OPTIMIZER_POKAKRIBIERE_H
#define OPTIMIZER_POKAKRIBIERE_H

#include <cstddef>
#include "Optimizer.h"
#include "Vector.h"


template <size_t dim>
class PolakRibiere : public Optimizer<dim> {
    class alphaFunction : public Function<1> {
        const Function<dim>& f;
        const Vector<dim>& p;
        const Vector<dim>& x;

    public:
        alphaFunction(const Function<dim>& f, const Vector<dim>&p, const Vector<dim>&x) : Function(Limits(f, p, x)),
                                                                                        f(f), p(p), x(x) {}
        double operator() (const Vector<1>& alpha) {
            return f(x + p*alpha);
        }
    };

    class liniarOptimizator : Optimizer<1> {

    };

    Vector<dim> p;
    void step() {

    }

    void setup() {
        p = -Gradient<dim>(Optimizer<dim>::f, Optimizer<dim>::track.back().first);
    }

public:
    PolakRibiere(const Function<dim> &f, Criterion<dim>& crit) : Optimizer<dim>(f, crit) {}
};


#endif //OPTIMIZER_POKAKRIBIERE_H
