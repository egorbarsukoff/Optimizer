//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Point.h"
#include "Function.h"


//! @brief Абстрактный оптимизатор функций
//! \tparam dim
template <size_t dim>
class Optimizer {
protected:
    //! Пройденные точки
    Track<dim> track;

    const Function<dim>& f;

    //! Критерий остановки
    const std::vector<Criterion<dim>*>& crits;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

    bool checkCrits() {
        bool ok = true;
        for (auto it = 0; it < crits.size() && ok; ++it) {
            if (!(*crits[it])(track))
                ok = false;
        }
        return ok;
    }
public:

    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(const Function<dim> &f, std::vector<Criterion<dim>*>& crits) : f(f), crits(crits) {}

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track<dim> optimize(const Point<dim> &start) {
        track = Track<dim>();
        track.push_back(start);
        while (checkCrits()) {
            step();
        }
        return track;
    }
};


#endif //OPTIMIZER_OPTIMIZER_H
