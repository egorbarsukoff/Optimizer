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
#include <numeric>
#include <cmath>


template <size_t dim>
class Vector;

template <size_t dim>
Vector<dim> pairWiseTransform(const Vector<dim> &a, const Vector<dim> &b, std::function<double(double, double)> f);


//! @brief Точка пространства
//! \tparam dim Размерность пространства
template <size_t dim>
class Vector {
protected:

    //! Хранит координаты точки
    std::array<double, dim> x;
public:

    //! Конструктор
    //! \param x Массив координат точки
    explicit Vector(std::array<double, dim> x) : x(std::move(x)) {};

    //! Конструктор нулевой точки
    Vector() : x() {
        for (auto& i : x)
            i = 0;
    };

    //! Конструктор копирования
    Vector(const Vector& p) : Vector(p.x) {};

    //! Конструктор перемещения
    Vector(Vector&& p) noexcept : Vector(std::move(p.x)) {};

    //! Создает точку со всеми нулевыми координатыми, кроме координаты n
    //! \param n
    explicit Vector(size_t n) : Vector() {
        x[n] = 1;
    }

    //! Возращает массив координат точек
    //! \return
    const std::array<double, dim> &getX() const {
        return x;
    }


    //!  Эвклидова норма вектора
    //! \return норма
    double norm() const {
        double sum = 0;
        for (double i : x)
            sum += i*i;
        return pow(sum, 1./2);
    }

    //! Оператор копирования
    //! \param b
    //! \return
    Vector<dim>& operator=(const Vector<dim>& b) {
        x = x.b;
        return *this;
    }

    //! Оператор перемещения
    //! \param b
    //! \return
    Vector<dim>& operator=(Vector<dim>&& b) noexcept {
        x = std::move(b.x);
        return *this;
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
    friend Vector<n> operator*(Vector<n> p, double a);

    //! Применяет функцию f попарно к элементам Point
    //! \tparam n Размерность
    //! \param a Первая Point
    //! \param b Вторая Point
    //! \param f Функция, которую надо пременить
    //! \return Результат
    template <size_t n>
    friend Vector<n> pairWiseTransform(const Vector<n> &a, const Vector<n> &b, std::function<double(double, double)> f);

    //! Вывод координат в круглых скобочках
    //! \tparam n Размерность
    //! \param o Поток вывода
    //! \param p Точка, которую необходимо вывести
    //! \return Измененный поток вывода
    template <size_t n>
    friend std::ostream& operator<<(std::ostream& o, const Vector<n>& p);
};


template <size_t dim>
Vector<dim> pairWiseTransform(const Vector<dim> &a, const Vector<dim> &b, std::function<double(double, double)> f) {
    assert(a.x.size() == b.x.size());
    Vector<dim> result(a.x);
    std::transform(result.x.begin(), result.x.end(), b.x.cbegin(), result.x.begin(), f);
    return result;
}

template <size_t dim>
Vector<dim> operator+(const Vector<dim> &a, const Vector<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::plus<double>());
}

template <size_t dim>
Vector<dim> operator-(const Vector<dim> &a, const Vector<dim> &b) {
    return pairWiseTransform<dim>(a, b, std::minus<double>());
}


template <size_t dim>
Vector<dim> operator*(Vector<dim> p, double a) {
    std::transform(p.x.begin(), p.x.end(), p.x.begin(), std::bind1st(std::multiplies<double>(), a));
    return p;
}

template <size_t n>
std::ostream& operator<<(std::ostream& o, const Vector<n>& p) {
    o << "( ";
    for (auto x : p.x) {
        o << x << " ";
    }
    o << ")";
}


template <size_t n>
using Track = std::vector<std::pair<Vector<n>, double >>;


#endif //OPTIMIZER_POINT_H
