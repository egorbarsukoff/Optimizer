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
    //! Конструктор по границам
    //! \param _bounds Пары точек для каждой размерности: левая и правая границы
    BoxDomain<dim> (std::array<std::array<double, 2>, dim> _bounds) : bounds(_bounds) {
        for (const std::array<double, dim>& b: bounds) {
            if (b[0] >= b[1])
                throw "Bad bounds";
        }
    }
    //! Конструктор окрестности
    //! \param p Центр окрестности
    //! \param eps Размер окрестности
    BoxDomain<dim> (Point<dim> p, double eps) {
        for (size_t i = 0; i < dim; ++i) {
            std::tie(bounds[i][0], bounds[i][1]) = std::tie(p[i] - eps, p[i] + eps);
        }
    }
    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    bool inDomain(const Point<dim>& p) const {
        return true;
    }
    //! Пересечние двух областей определения
    //! \param d Вторая область определения
    //! \return Результат
    template <size_t n>
    friend BoxDomain<n> operator*(const BoxDomain<n>& a, const BoxDomain<n>& b);
};


template <size_t n>
BoxDomain<n> operator*(const BoxDomain<n>& a, const BoxDomain<n>& b) {
    std::array<std::array<double, 2>, n> new_box;
    for (size_t i = 0; i < n; ++i) {
        std::tie(new_box[i][0], new_box[i][1]) = std::tie(std::min(a[i][0], b[i][0]), std::max(a[i][1], b[i][1]));
    }
}

#endif //OPTIMIZER_DOMAIN_H
