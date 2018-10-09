//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H


#include "Vector.h"
#include "CommonRandom.h"


//! @brief Область определения типа коробка
class BoxDomain {
    std::vector<std::array<double, 2>> bounds;
public:
    //! Конструктор по границам
    //! \param _bounds Пары точек для каждой размерности: левая и правая границы
    explicit BoxDomain (std::vector<std::array<double, 2>> _bounds);

    //! Конструктор окрестности
    //! \param p Центр окрестности
    //! \param eps Размер окрестности
    BoxDomain (Vector p, double eps);

    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    bool inDomain(const Vector& p) const;

    //! Случайная Point в области определения
    //! \return
    Vector randomPoint() const;

    //! Мера Лебега области
    //! \return
    double measure() const;

    //! Пересечние двух областей определения
    //! \param d Вторая область определения
    //! \return Результат
    friend BoxDomain operator*(const BoxDomain& a, const BoxDomain& b);
};




#endif //OPTIMIZER_DOMAIN_H
