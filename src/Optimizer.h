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
    //! Критерий остановки
    const Criterion<dim>& crit;
    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;
public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(const Criterion<dim>& crit) : crit(crit) {}
    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track<dim> optimize(const Function<dim> &f, const Point<dim> &start) {
        Track<dim> track;
        track.push_back(start);
        while (crit(track)) {
            step();
        }
        return track;
    }
};


#endif //OPTIMIZER_OPTIMIZER_H
