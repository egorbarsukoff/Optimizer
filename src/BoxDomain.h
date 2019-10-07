//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_DOMAIN_H
#define OPTIMIZER_DOMAIN_H

#include "Random.h"
#include <array>
#include <Eigen/Core>

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
    BoxDomain(const Eigen::VectorXd &p, double eps);

    //! Проверка, что точка находится внутри области определения
    //! \param p Проверяемая точка
    //! \return Результат
    [[nodiscard]] bool inDomain(const Eigen::VectorXd &p) const;

    //! Случайная Point в области определения
    //! \return
    [[nodiscard]] Eigen::VectorXd randomPoint() const;

    //! Мера Лебега области
    //! \return
    [[nodiscard]] double measure() const;

    [[nodiscard]] size_t dim() const;

    //! Такая $\alpha$, что $x + \alpha p$, лежит на границе области
    //! \return $\alpha$
    [[nodiscard]] double intersectCoeff(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const;

    //! Пересечние двух областей определения
    //! \param d Вторая область определения
    //! \return Результат
    friend BoxDomain operator*(const BoxDomain& a, const BoxDomain& b);
};




#endif //OPTIMIZER_DOMAIN_H
