#include <iostream>

#include <optim/NewtonOptimizer.h>
#include "optim/Criterion.h"
#include "optim/RandomSearch.h"
#include "optim/Functions.h"

#include "optim/TaskBuilder.h"

int main(int argc, char *argv[]) {
    int fn;
    TaskBuilder task;
    std::cout << "Оптимизируемая функиця:\n"
                 "1 - Функция Розенброка\n"
                 "2 - x^2 + 3y^2 + 6z^2 + 2xy\n"
                 "3 - sin(w) * sin(x) * y / cos(z * 10)\n";
    std::cin >> fn;
    std::cout << "Границы в формате \n x_l, x_r\ny_l y_r\n...\n";
    if (fn == 1) {
        double xl, xr, yl, yr;
        std::cin >> xl >> xr >> yl >> yr;
        task.set_f<Rosenbrock>(BoxDomain{{{{xl, xr}, {yl, yr}}}});
    } else if (fn == 2) {
        double xl, xr, yl, yr, zl, zr;
        std::cin >> xl >> xr >> yl >> yr >> zl >> zr;
        task.set_f<SquareFunction3>(BoxDomain{{{{xl, xr}, {yl, yr}, {zl, zr}}}});
    } else if (fn == 3) {
        double wl, wr, xl, xr, yl, yr, zl, zr;
        std::cin >> wl >> wr >> xl >> xr >> yl >> yr >> zl >> zr;
        task.set_f<SinCos4>(BoxDomain{{{{wl, wr}, {xl, xr}, {yl, yr}, {zl, zr}}}});
    } else {
        std::cout << "Ошибка ввода границ\n";
        std::exit(0);
    }
    std::cout << "Добавьте критерии остановки:\n"
                 "1 - максимальное количество итераций\n"
                 "2 - масимальное количество итераций ез обновления (для случайного поиска)\n"
                 "3 - (f_{i-1} - f_i)/f_i < eps\n"
                 "-1 - Выход из добавление критериев";
    int i;
    while (true) {
        std::cin >> i;
        if (i == 1) {
            std::cout << "Введите максимальное количство итераций: ";
            unsigned it;
            std::cin >> it;
            task.add_crit<MaxN>(it);
            std::cout << "Критерий добавлен\n";
        } else if (i == 2) {
            std::cout << "Введите максимальное количство итераций без обновления: ";
            unsigned it;
            std::cin >> it;
            task.add_crit<NWithoutUpdates>(it);
            std::cout << "Критерий добавлен\n";
        } else if (i == 3) {
            std::cout << "Введите eps: ";
            double eps;
            std::cin >> eps;
            task.add_crit<FunctionChange>(eps);
            std::cout << "Критерий добавлен\n";
        } else {
            break;
        }
    }
    std::cout << "Начальное приблежение: ";
    if (fn == 1) {
        int x, y;
        std::cin >> x >> y;
        task.set_start(x, y);
    } else if (fn == 2) {
        int x, y, z;
        std::cin >> x >> y >> z;
        task.set_start(x, y, z);
    } else if (fn == 3) {
        int w, x, y, z;
        std::cin >> w >> x >> y >> z;
        task.set_start(w, x, y, z);
    }
    std::cout << "Метод:\n"
                 "1 - Ньютона\n"
                 "2 - Случайный поиск\n";
    std::cin >> fn;
    Eigen::VectorXd x;
    double y;
    if (fn == 1) {
        std::tie(x, y) = task.start_and_reset<NewtonOptimizer>();
    } else if (fn == 2) {
        std::tie(x, y) = task.start_and_reset<RandomSearch>();
    } else {
        std::cout << "Ошибка ввода\n";
        std::exit(0);
    }

    std::cout << "Минимум функции:\n f(" << x.transpose() << ") = " << y;;


}