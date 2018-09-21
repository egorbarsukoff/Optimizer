//
// Created by egorb on 21.09.2018.
//

#include "Optimizer.h"

Track Optimizer::optimize(Function f, Point start) {
    Track track;
    track.push_back(start);
    while (crit(track)) {
        step();
    }
    return track;
}
