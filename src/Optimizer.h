//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Vector.h"
#include "Function.h"



//! @brief Абстрактный оптимизатор функций
class Optimizer {
protected:

    //! Пройденные точки
    Track track;

    //! Количество итераций
    size_t n;
    //! Оптимизируемая функция
    std::shared_ptr<const Function> f;

    //! Критерий остановки
    std::shared_ptr<Criterion> crit;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(const Function &f, Criterion& crit);

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track optimize(const Vector &start);
};


#endif //OPTIMIZER_OPTIMIZER_H
