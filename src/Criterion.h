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
