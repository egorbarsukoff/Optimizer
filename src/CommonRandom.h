//
// Created by egorb on 23.09.2018.
//

#ifndef OPTIMIZER_COMMONRANDOM_H
#define OPTIMIZER_COMMONRANDOM_H

#include <random>
#include <cassert>


//! @brief Синглетон ГПСЧ
class CommonRandom {
    static std::mt19937& get_mt() {
        static std::mt19937 mt;
        return mt;
    }
public:
    CommonRandom() = delete;
    CommonRandom (const CommonRandom&) = delete;
    CommonRandom& operator= (const CommonRandom&) = delete;

    //! Равномерное распределение на (a, b)
    //! \param a
    //! \param b
    //! \return
    static double getU(double a = 0, double b = 1) {
        return std::uniform_real_distribution<double>(a, b)(CommonRandom::get_mt());
    }

    //! Распределение Бернулии с вероятностью p
    //! \param p
    //! \return
    static bool getB(double p) {
        assert(p < 1);
        return CommonRandom::getU(0, 1) < p;
    }
};


#endif //OPTIMIZER_COMMONRANDOM_H
