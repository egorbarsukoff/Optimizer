//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H


#include "Vector.h"
#include "CommonRandom.h"


//! @brief Область определения типа коробка
//! \tparam dim Размерность
class BoxDomain {
    std::vector<std::array<double, 2>> bounds;
public:
    //! Конструктор по границам
    //! \param _bounds Пары точек для каждой размерности: левая и правая границы
    explicit BoxDomain (std::vector<std::array<double, 2>> _bounds) : bounds(std::move(_bounds)) {
        for (const std::array<double, 2>& b: bounds) {
            if (b[0] >= b[1])
                throw "Bad bounds"; //TODO: Сделать нормальное исключение
        }
    }

    //! Конструктор окрестности
    //! \param p Центр окрестности
    //! \param eps Размер окрестности
    BoxDomain (Vector p, double eps) : bounds(p.getDim()) {
        for (size_t i = 0; i < p.getDim(); ++i) {
            bounds[i][0] = p[i] - eps;
            bounds[i][1] = p[i] + eps;
        }
    }

    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    bool inDomain(const Vector& p) const {
        for (int i = 0; i < p.getDim(); ++i) {
            if (bounds[i][0] > p[i] || bounds[i][1] < p[i])
                return false;
        }
        return true;
    }

    //! Случайная Point в области определения
    //! \return
    Vector randomPoint() const {
        Vector p(bounds.size());
        for (size_t i = 0; i < p.getDim(); ++i) {
            p[i] = CommonRandom::getU(bounds[i][0], bounds[i][1]);
        }
        return p;
    }

    //! Мера Лебега области
    //! \return
    double measure() const {
        double res = 1;
        for (int i = 0; i < bounds.size(); ++i) {
            res *= bounds[i][1] - bounds[i][0];
        }
        return res;
    }

    //! Пересечние двух областей определения
    //! \param d Вторая область определения
    //! \return Результат
    friend BoxDomain operator*(const BoxDomain& a, const BoxDomain& b);
};



BoxDomain operator*(const BoxDomain& a, const BoxDomain& b) {
    std::vector<std::array<double, 2>> new_box(a.bounds.size());
    for (size_t i = 0; i < new_box.size(); ++i) {
        new_box[i][0] = std::max(a.bounds[i][0], b.bounds[i][0]);
        new_box[i][1] = std::min(a.bounds[i][1], b.bounds[i][1]);
        assert(new_box[i][0] < new_box[i][1]);
    }
    return BoxDomain(new_box);
}

#endif //OPTIMIZER_DOMAIN_H
