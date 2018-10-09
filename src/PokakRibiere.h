//
// Created by egorb on 27.09.2018.
//

#ifndef OPTIMIZER_POKAKRIBIERE_H
#define OPTIMIZER_POKAKRIBIERE_H

#include <cstddef>
#include "Optimizer.h"
#include "Vector.h"

//TODO: Реализовать
class PolakRibiere : public Optimizer {
//    class alphaFunction : public Function<1> {
//        const Function& f;
//        const Vector& p;
//        const Vector& x;
//
//    public:
//        alphaFunction(const Function& f, const Vector&p, const Vector&x) : Function(Limits(f, p, x)),
//                                                                                        f(f), p(p), x(x) {}
//        double operator() (const Vector<1>& alpha) {
//            return f(x + p*alpha);
//        }
//    };
//
//    class liniarOptimizator : Optimizer {
//
//    };

    Vector p;
    void step() {

    }

    void setup() {
        p = -Gradient(Optimizer::f, Optimizer::track.back().first);
    }

public:
    PolakRibiere(const Function &f, Criteria& crit) : Optimizer(f, crit) {}
};


#endif //OPTIMIZER_POKAKRIBIERE_H
