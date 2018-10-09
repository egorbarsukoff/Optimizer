//
// Created by egorb on 10.10.2018.
//

#include "../Criteria.h"

CriterionPack::CriterionPack (std::vector<Criteria*> pack) : pack(pack) {}

bool CriterionPack::operator() (const Track& track, size_t n) {
    bool ans = true;
    for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
        ans = (**it)(track, n) && ans;
    }
    return ans;
}


MaxN::MaxN(size_t maxN) : Criteria(), maxN(maxN) {}

bool MaxN::operator() (const Track& track, size_t n) {
    return track.size() < maxN;
}


NWithoutUpdates::NWithoutUpdates(size_t n) : Criteria(), n(n), counter(0), last_len(0) {}

bool NWithoutUpdates::operator() (const Track& track, size_t nIt) {
    if (track.size() != last_len) {
        last_len = track.size();
        counter = 0;
    } else
        ++counter;
    return counter < n;
}


FunctionChange::FunctionChange(double eps): eps(eps) {}

bool FunctionChange::operator() (const Track& track, size_t nIt) {
    if (track.size() != 1 && (track[track.size() - 2].second -
                              track[track.size() - 1].second)/track[track.size() - 1].second < eps)
        return false;
    return true;
}


GradientCriterion::GradientCriterion(double eps): eps(eps) {}

bool GradientCriterion::operator() (const Track& track, size_t nIt) {
    if (track.back().first.norm() < eps)
        return false;
    return true;
}