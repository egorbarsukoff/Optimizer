//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criteria.h"
#include "Vector.h"
#include "Function.h"



//! @brief Абстрактный оптимизатор функций
class Optimizer {
protected:

    //! Пройденные точки
    Track track;

    //! Количество итераций
    size_t n;
    //TODO: Убрать ссылки на внешние объекты
    //! Оптимизируемая функция
    const Function& f;

    //! Критерий остановки
    Criteria& crit;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(const Function &f, Criteria& crit);

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track optimize(const Vector &start);
};


#endif //OPTIMIZER_OPTIMIZER_H
