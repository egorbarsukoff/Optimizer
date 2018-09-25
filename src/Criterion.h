//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include <initializer_list>
#include "Point.h"


//! @brief Абстрактный критерий остановки
//! \tparam dim Размерность
template <size_t dim>
class Criterion {
public:

    //! Проверка абстрактного критерия
    //! \param track Путь оптимизатора
    //! \return Выполнен критерий или нет
    virtual bool operator() (const Track<dim>& track, size_t n) = 0 ;
};



//! Композиция критериев
//! \tparam dim Размерность
template <size_t dim>
class CriterionPack : public Criterion<dim> {

    //! Критерии, которые требуется проверять
    std::vector<Criterion<dim>*> pack;
public:
    //! Конструктор композиции
    //! \param pack Набор критериев
    explicit CriterionPack (std::vector<Criterion<dim>*> pack) : pack(pack) {}

    //! Проверка критериев
    //! \param track
    //! \return Выполнены ли все критерии
    bool operator() (const Track<dim>& track, size_t n) {
        bool ans = true;
        for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
            ans = (**it)(track, n) && ans;
        }
        return ans;
    }

};



//! @brief Критерий максимального количеста итераций
//! \tparam dim Размерность
template <size_t dim>
class MaxN : public Criterion<dim>{

    //! Максимальное коичество итераций
    size_t maxN;
public:

    //! Конструктор критерия
    //! \param maxN Максимальное количество итераций
    explicit MaxN(size_t maxN) : Criterion<dim>(), maxN(maxN) {}

    //! Проверка критерия
    //! \param track
    //! \return Выполнен ли критерий
    bool operator() (const Track<dim>& track, size_t n) {
        return track.size() < maxN;
    }
};

//! @brief Максимальное количество итераций без обновления (для RandomSearch)
//! \tparam dim Размерность
template <size_t dim>
class NWithoutUpdates : public Criterion<dim> {
    size_t n;
    size_t counter;
    size_t last_len;

public:
    explicit NWithoutUpdates(size_t n) : Criterion<dim>(), n(n), counter(0), last_len(0) {}
    bool operator() (const Track<dim>& track, size_t nIt) {
        if (track.size() != last_len) {
            last_len = track.size();
            counter = 0;
        } else
            ++counter;
        return counter < n;
    }
};


#endif //OPTIMIZER_CRITERION_H
