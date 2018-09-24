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

    //! Количество итераций
    size_t n;

    //! Оптимизируемая функция
    const Function<dim>& f;

    //! Критерий остановки
    const Criterion<dim>& crit;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(const Function<dim> &f, const Criterion<dim>& crit) : f(f), crit(crit), n(0) {}

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track<dim> optimize(const Point<dim> &start) {
        track = Track<dim>();
        track.push_back(start);
        while (crit(track, n)) {
            step();
            ++n;
        }
        return track;
    }
};


#endif //OPTIMIZER_OPTIMIZER_H
