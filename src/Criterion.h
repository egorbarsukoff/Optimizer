//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include <memory>
#include <valarray>
#include <vector>
#include "Track.h"


//! @brief Абстрактный критерий остановки
class Criterion {
public:

    //! Проверка абстрактного критерия
    //! \param track Путь оптимизатора
    //! \return Выполнен критерий или нет
    virtual bool operator() (const Track& track, size_t n) = 0;
    virtual void reset() {}

    virtual std::shared_ptr<Criterion> copy() const = 0;
};



//! Композиция критериев
class CriterionPack : public Criterion {

    //! Критерии, которые требуется проверять
    std::vector<std::shared_ptr<Criterion>> pack; //TODO не хранить ссылки на внешние объекты!
public:
    //! Конструктор композиции
    explicit CriterionPack (std::vector<Criterion*> crits);

    //! Проверка критериев
    //! \param track
    //! \return Выполнены ли все критерии
    bool operator() (const Track& track, size_t n) override;

    std::shared_ptr<Criterion> copy() const override;

};


//! @brief Критерий максимального количеста итераций
class MaxN : public Criterion{

    //! Максимальное коичество итераций
    size_t maxN;
public:

    //! Конструктор критерия
    //! \param maxN Максимальное количество итераций
    explicit MaxN(size_t maxN);

    //! Проверка критерия
    //! \param track
    //! \return Выполнен ли критерий
    bool operator() (const Track& track, size_t n) override;

    std::shared_ptr<Criterion> copy() const override;
};

//! @brief Максимальное количество итераций без обновления (для RandomSearch)
//! \tparam dim Размерность
class NWithoutUpdates : public Criterion {
    size_t n;
    size_t counter;
    size_t last_len;
    NWithoutUpdates(size_t n, size_t counter, size_t last_len);
public:
    virtual void reset() override;
    explicit NWithoutUpdates(size_t n);
    bool operator() (const Track& track, size_t nIt);
    std::shared_ptr<Criterion> copy() const override;
};

//! @brief Критерий (f_{i-1} - f_i)/f_i < eps$
//! \tparam dim размерность
class FunctionChange : public Criterion {
    double eps;
public:
    explicit FunctionChange(double eps);
    bool operator() (const Track& track, size_t nIt) override;

    std::shared_ptr<Criterion> copy() const override;
};


//! @brief Критерий нормы градиента
//! \tparam dim Размерность
class GradientCriterion : public Criterion {
    double eps;
public:
    explicit GradientCriterion(double eps);
    bool operator() (const Track& track, size_t nIt);

    std::shared_ptr<Criterion> copy() const override;
};




#endif //OPTIMIZER_CRITERION_H
