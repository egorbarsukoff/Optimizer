//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H


#include "Point.h"
#include "CommonRandom.h"


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
            bounds[i][0] = p[i] - eps;
            bounds[i][1] = p[i] + eps;
        }
    }

    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    bool inDomain(const Point<dim>& p) const {
        return true;
    }

    //! Случайная Point в области определения
    //! \return
    Point<dim> randomPoint() const {
        Point<dim> p;
        for (size_t i = 0; i < dim; ++i) {
            p[i] = CommonRandom::getU(bounds[i][0], bounds[i][1]);
        }
        return p;
    }

    //! Мера Лебега области
    //! \return
    double measure() const {
        double res = 1;
        for (int i = 0; i < dim; ++i) {
            res *= bounds[i][1] - bounds[i][0];
        }
        return res;
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
        new_box[i][0] = std::max(a.bounds[i][0], b.bounds[i][0]);
        new_box[i][1] = std::min(a.bounds[i][1], b.bounds[i][1]);
        assert(new_box[i][0] < new_box[i][1]);
    }
}

#endif //OPTIMIZER_DOMAIN_H
