//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H


#include <initializer_list>
#include "Point.h"


//! @brief Абстрактный критерий остановки
//! \tparam n Размерность
template <size_t n>
class Criterion {
public:

    //! Проверка абстрактного критерия
    //! \param track Путь оптимизатора
    //! \return Выполнен критерий или нет
    virtual bool operator() (const Track<n>& track) const = 0 ;
};

//! Композиция критериев
//! \tparam n Размерность
template <size_t n>
class CriterionPack : public Criterion<n> {

    //! Критерии, которые требуется проверять
    std::vector<Criterion<n>*> pack;
public:
    //! Конструктор композиции
    //! \param pack Набор критериев
    explicit CriterionPack (std::vector<Criterion<n>*> pack) : pack(pack) {}

    //! Проверка критериев
    //! \param track
    //! \return Выполнены ли все критерии
    bool operator() (const Track<n>& track) const {
        bool ans = true;
        for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
            ans = (**it)(track) && ans;
        }
        return ans;
    }

};


template <size_t n>
class MaxN : public Criterion<n>{
    size_t maxN;
public:
    explicit MaxN(size_t maxN) : Criterion<n>(), maxN(maxN) {}
    bool operator() (const Track<n>& track) const {
        return track.size() < maxN;
    }
};


#endif //OPTIMIZER_CRITERION_H
