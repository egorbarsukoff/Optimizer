//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include "Vector.h"

//TODO: Сделать фабрику
//! @brief Абстрактный критерий остановки
class Criteria {
public:

    //! Проверка абстрактного критерия
    //! \param track Путь оптимизатора
    //! \return Выполнен критерий или нет
    virtual bool operator() (const Track& track, size_t n) = 0 ;
};



//! Композиция критериев
class CriterionPack : public Criteria {

    //! Критерии, которые требуется проверять
    std::vector<Criteria*> pack; //TODO не хранить ссылки на внешние объекты!
public:
    //! Конструктор композиции
    //! \param pack Набор критериев
    explicit CriterionPack (std::vector<Criteria*> pack);

    //! Проверка критериев
    //! \param track
    //! \return Выполнены ли все критерии
    bool operator() (const Track& track, size_t n);

};


//! @brief Критерий максимального количеста итераций
class MaxN : public Criteria{

    //! Максимальное коичество итераций
    size_t maxN;
public:

    //! Конструктор критерия
    //! \param maxN Максимальное количество итераций
    explicit MaxN(size_t maxN);

    //! Проверка критерия
    //! \param track
    //! \return Выполнен ли критерий
    bool operator() (const Track& track, size_t n);
};

//! @brief Максимальное количество итераций без обновления (для RandomSearch)
//! \tparam dim Размерность
class NWithoutUpdates : public Criteria {
    size_t n;
    size_t counter;
    size_t last_len;

public:
    explicit NWithoutUpdates(size_t n);
    bool operator() (const Track& track, size_t nIt);
};

//! @brief Критерий (f_{i-1} - f_i)/f_i < eps$
//! \tparam dim размерность
class FunctionChange : public Criteria {
    double eps;
public:
    explicit FunctionChange(double eps);
    bool operator() (const Track& track, size_t nIt);
};


//! @brief Критерий нормы градиента
//! \tparam dim Размерность
class GradientCriterion : public Criteria {
    double eps;
public:
    explicit GradientCriterion(double eps);
    bool operator() (const Track& track, size_t nIt);
};




#endif //OPTIMIZER_CRITERION_H
