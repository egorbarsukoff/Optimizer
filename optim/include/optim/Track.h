//
// Created by egor on 9/16/19.
//

#ifndef OPTIMIZER_SRC_CPP_TRACK_H
#define OPTIMIZER_SRC_CPP_TRACK_H

#include <Eigen/Core>
#include <vector>

//! @brief Точка трека
struct F {
    Eigen::VectorXd x;
    double y;
    F(Eigen::VectorXd x, double y);
};

using Track = std::vector<F>;

#endif //OPTIMIZER_SRC_CPP_TRACK_H
