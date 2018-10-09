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



//! @brief Точка пространства
class Vector {
protected:

    //! Хранит координаты точки
    std::vector<double> x;
public:

    //! Конструктор
    //! \param x Массив координат точки
    explicit Vector(std::vector<double> x);

    //! Конструктор нулевой точки
    Vector(size_t dim);

    //! Конструктор копирования
    Vector(const Vector& p);

    //! Конструктор перемещения
    Vector(Vector&& p) noexcept;

    //! Создает точку со всеми нулевыми координатыми, кроме координаты n
    //! \param n
    explicit Vector(size_t dim, size_t n);

    //! Возращает массив координат точек
    //! \return
    const std::vector<double> &getX() const;

    size_t getDim() const;

    //!  Эвклидова норма вектора
    //! \return норма
    double norm() const;

    //! Оператор копирования
    //! \param b
    //! \return
    Vector& operator=(const Vector& b) = default;

    //! Оператор перемещения
    //! \param b
    //! \return
    Vector& operator=(Vector&& b) noexcept = default;

    //! Возращает константное значение i-ой координаты
    //! \param i
    //! \return
    double operator[](size_t i) const;

    //! Возращает неконстантное значение i-ой координаты
    //! \param i
    //! \return
    double& operator[](size_t i);

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
