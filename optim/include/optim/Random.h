//
// Created by egorb on 23.09.2018.
//

#ifndef OPTIMIZER_COMMONRANDOM_H
#define OPTIMIZER_COMMONRANDOM_H

#include <random>
#include <cassert>


//! @brief Синглетон ГПСЧ
class Random {
    static std::mt19937& get_mt();
public:
    Random() = delete;
    Random (const Random&) = delete;
    Random& operator= (const Random&) = delete;

    //! Равномерное распределение на (a, b)
    //! \param a
    //! \param b
    //! \return
    static double getU(double a = 0, double b = 1);

    //! Распределение Бернулии с вероятностью p
    //! \param p
    //! \return
    static bool getB(double p);
};


#endif //OPTIMIZER_COMMONRANDOM_H
