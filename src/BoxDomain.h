//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H


#include "Point.h"


//! @brief Область определения типа коробка
//! \tparam dim Размерность
template <size_t dim>
class BoxDomain {
    std::array<std::array<double, 2>, dim> bounds;
public:
    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    bool inDomain(const Point<dim>& p) const {
        return true;
    };
    //! Пересечние двух областей определения
    //! \param d Вторая область определения
    //! \return Результат
    BoxDomain<dim> intersect(const BoxDomain<dim>& d);
};


#endif //OPTIMIZER_DOMAIN_H
