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



class Vector;

template <size_t dim>
Vector pairWiseTransform(const Vector &a, const Vector &b, std::function<double(double, double)> f);

//TODO: отказаться от шаблонов!!!!
//! @brief Точка пространства
//! \tparam dim Размерность пространства
class Vector {
protected:

    //! Хранит координаты точки
    std::vector<double> x;
public:

    //! Конструктор
    //! \param x Массив координат точки
    explicit Vector(std::vector<double> x) : x(std::move(x)) {};

    //! Конструктор нулевой точки
    Vector(size_t dim) : x(dim) {}

    //! Конструктор копирования
    Vector(const Vector& p) : Vector(p.x) {};

    //! Конструктор перемещения
    Vector(Vector&& p) noexcept : Vector(std::move(p.x)) {};

    //! Создает точку со всеми нулевыми координатыми, кроме координаты n
    //! \param n
    explicit Vector(size_t dim, size_t n) : Vector(dim) {
        x[n] = 1;
    }

    //! Возращает массив координат точек
    //! \return
    const std::vector<double> &getX() const {
        return x;
    }

    size_t getDim() const {
        return x.size();
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
    Vector& operator=(const Vector& b) {
        x = b.x;
        return *this;
    }

    //! Оператор перемещения
    //! \param b
    //! \return
    Vector& operator=(Vector&& b) noexcept {
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
    friend Vector operator*(Vector p, double a);

    //! Применяет функцию f попарно к элементам Point
    //! \tparam n Размерность
    //! \param a Первая Point
    //! \param b Вторая Point
    //! \param f Функция, которую надо пременить
    //! \return Результат
    friend Vector pairWiseTransform(const Vector &a, const Vector &b, std::function<double(double, double)> f);

    //! Вывод координат в круглых скобочках
    //! \tparam n Размерность
    //! \param o Поток вывода
    //! \param p Точка, которую необходимо вывести
    //! \return Измененный поток вывода
    friend std::ostream& operator<<(std::ostream& o, const Vector& p);
};

Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
Vector operator*(Vector p, double a);


//TODO Класс трека
using Track = std::vector<std::pair<Vector, double >>;


#endif //OPTIMIZER_POINT_H
