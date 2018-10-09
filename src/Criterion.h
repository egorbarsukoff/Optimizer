//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include "Vector.h"

//TODO: Сделать фабрику
//! @brief Абстрактный критерий остановки
//! \tparam dim Размерность
class Criterion {
public:

    //! Проверка абстрактного критерия
    //! \param track Путь оптимизатора
    //! \return Выполнен критерий или нет
    virtual bool operator() (const Track& track, size_t n) = 0 ;
};



//! Композиция критериев
//! \tparam dim Размерность
class CriterionPack : public Criterion {

    //! Критерии, которые требуется проверять
    std::vector<Criterion*> pack;
public:
    //! Конструктор композиции
    //! \param pack Набор критериев
    explicit CriterionPack (std::vector<Criterion*> pack) : pack(pack) {}

    //! Проверка критериев
    //! \param track
    //! \return Выполнены ли все критерии
    bool operator() (const Track& track, size_t n) {
        bool ans = true;
        for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
            ans = (**it)(track, n) && ans;
        }
        return ans;
    }

};



//! @brief Критерий максимального количеста итераций
//! \tparam dim Размерность
class MaxN : public Criterion{

    //! Максимальное коичество итераций
    size_t maxN;
public:

    //! Конструктор критерия
    //! \param maxN Максимальное количество итераций
    explicit MaxN(size_t maxN) : Criterion(), maxN(maxN) {}

    //! Проверка критерия
    //! \param track
    //! \return Выполнен ли критерий
    bool operator() (const Track& track, size_t n) {
        return track.size() < maxN;
    }
};

//! @brief Максимальное количество итераций без обновления (для RandomSearch)
//! \tparam dim Размерность
class NWithoutUpdates : public Criterion {
    size_t n;
    size_t counter;
    size_t last_len;

public:
    explicit NWithoutUpdates(size_t n) : Criterion(), n(n), counter(0), last_len(0) {}
    bool operator() (const Track& track, size_t nIt) {
        if (track.size() != last_len) {
            last_len = track.size();
            counter = 0;
        } else
            ++counter;
        return counter < n;
    }
};

//! @brief Критерий (f_{i-1} - f_i)/f_i < eps$
//! \tparam dim размерность
class FunctionChange : public Criterion {
    double eps;
public:
    explicit FunctionChange(double eps): eps(eps) {}
    bool operator() (const Track& track, size_t nIt) {
        if (track.size() != 1 && (track[track.size() - 2].second -
            track[track.size() - 1].second)/track[track.size() - 1].second < eps)
            return false;
        return true;
    }
};


//! @brief Критерий нормы градиента
//! \tparam dim Размерность
class GrdientCriterion : public Criterion {
    double eps;
public:
    explicit GrdientCriterion(double eps): eps(eps) {}
    bool operator() (const Track& track, size_t nIt) {
        if (track.back().first.norm() < eps)
            return false;
        return true;
    }
};




#endif //OPTIMIZER_CRITERION_H
