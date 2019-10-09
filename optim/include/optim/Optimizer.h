//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H


#include <vector>
#include "Criterion.h"
#include "Function.h"



//! @brief Абстрактный оптимизатор функций
class Optimizer {
protected:

    //! Пройденные точки
    Track track;

    //! Оптимизируемая функция
    std::unique_ptr<const AbstractFunction> f;
    //! Критерий остановки
    std::unique_ptr<Criterion> crit;

    //! Количество итераций
    size_t n;

    //! Абстрактный шаг оптимизатора
    virtual void step() = 0;

    //! Сброс оптимизатора
    virtual void reset();

public:
    //! Конструктор класса
    //! \param crit Кртерий остановки
    explicit Optimizer(std::unique_ptr<AbstractFunction> f, std::unique_ptr<Criterion> crit);

    void set_f(std::unique_ptr<const AbstractFunction> f);

    //! Старт оптимизации
    //! \param f Функция, которая будет оптимизироваться
    //! \param start Начальная точка
    //! \return Путь оптимизатора
    Track optimize(const Eigen::VectorXd &start);
};


#endif //OPTIMIZER_OPTIMIZER_H
