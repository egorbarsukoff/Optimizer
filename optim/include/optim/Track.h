//
// Created by egor on 9/16/19.
//

#ifndef OPTIMIZER_SRC_CPP_TRACK_H
#define OPTIMIZER_SRC_CPP_TRACK_H

#include <Eigen/Core>
#include <vector>

struct F {
    Eigen::VectorXd x;
    double y;
    F(Eigen::VectorXd x, double y);
};

class Track : public std::vector<F>{
public:

};

#endif //OPTIMIZER_SRC_CPP_TRACK_H
