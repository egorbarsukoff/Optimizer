//
// Created by egorb on 21.09.2018.
//

#ifndef OPTIMIZER_POINT_H
#define OPTIMIZER_POINT_H

#include <array>
#include <vector>
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <functional>


template <size_t dim>
class Point;

template <size_t dim>
Point<dim> pairWiseTransform(const Point<dim> &a, const Point<dim> &b, std::function<double(double, double)> f);


//! @brief Точка пространства
//! \tparam dim Размерность пространства
template <size_t dim>
class Point {
protected:
    //! Хранит координаты точки
    std::array<double, dim> x;
public:
    //! Конструктор
    //! \param x Массив координат точки
    explicit Point(std::array<double, dim> x) : x(std::move(x)) {};
    //! Конструктор нулевой точки
    Point() : x() {
        for (auto& i : x)
            i = 0;
    };
    //! Конструктор копирования
    Point(const Point& p) : Point(p.x) {};
    //! Конструктор перемещения
    Point(Point&& p) noexcept : Point(std::move(p.x)) {};
    //! Создает точку со всеми нулевыми координатыми, кроме координаты n
    //! \param n
    explicit Point(size_t n) : Point() {
        x[n] = 1;
    }
    //! Возращает массив координат точек
    //! \return
    const std::array<double, dim> &getX() const {
        return x;
    }
    //! Возращает константное значение i-ой координаты
    //! \param i
    //! \return
    double operator[](size_t i) const {
        assert(i < x.size() && i >= 0);
        return x[i];
    }
    //! Возращает неконстантное значение i-ой координаты
    //! \param i
    //! \return
    double& operator[](size_t i) {
        assert(i < x.size() && i >= 0);
        return x[i];
    }
    //! Умножение на скаляр
    //! \tparam dim Размерность
    //! \param a Скаляр
    //! \return Резульат
    template <size_t n>
    friend Point<n> operator*(Point<n> p, double a);

    //! Применяет функцию f попарно к элементам Point
    //! \tparam n Размерность
    //! \param a Первая Point
    //! \param b Вторая Point
    //! \param f Функция, которую надо пременить
    //! \return Результат
    template <size_t n>
    friend Point<n> pairWiseTransform(const Point<n> &a, const Point<n> &b, std::function<double(double, double)> f);
};

//! @brief Применяет функцию f попарно к элементам Point
//! \tparam n Размерность
//! \param a Первая Point
//! \param b Вторая Point
//! \param f Функция, которую надо пременить
//! \return Результат
template <size_t dim>
Point<dim> pairWiseTransform(const Point<dim> &a, const Point<dim> &b, std::function<double(double, double)> f) {
    assert(a.x.size() == b.x.size());
    Point<dim> result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), result.x.begin(), f);
    return result;
}


//! Попарное сложение двух Point
//! \tparam dim Размерность
//! \param a Левый операнд
//! \param b Правый операнд
//! \return Резульат
template <size_t dim>
Point<dim> operator+(const Point<dim> &a, const Point<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::plus<double>());
}

//! Попарное вычитание двух Point
//! \tparam dim Размерность
//! \param a Левый операнд
//! \param b Правый операнд
//! \return Резульат
template <size_t dim>
Point<dim> operator-(const Point<dim> &a, const Point<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::minus<double>());
}

//! Умножение на скаляр
//! \tparam dim размерность
//! \param a Скаляр
//! \return Резульат
template <size_t dim>
Point<dim> operator*(Point<dim> p, double a) {
    std::transform(p.x.begin(), p.x.end(), p.x.begin(), std::bind1st(std::multiplies<double>(), a));
    return p;
}


template <size_t n>
using Track = std::vector<Point<n>>;


#endif //OPTIMIZER_POINT_H
