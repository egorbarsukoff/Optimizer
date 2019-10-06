//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Function.h"
#include <valarray>



//! @brief Абстрактный оптимизатор функций
class Optimizer {
protected:

    //! Пройденные точки
    Track track;

    //! Количество итераций
    size_t n;
    //! Оптимизируемая функция
    std::unique_ptr<const Function> f;

    //! Критерий остановки
    std::unique_ptr<Criterion> crit;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(std::unique_ptr<Function> f, std::unique_ptr<Criterion> crit);

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track optimize(const std::valarray<double> &start);
};


#endif //OPTIMIZER_OPTIMIZER_H
