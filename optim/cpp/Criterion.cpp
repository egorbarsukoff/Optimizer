//
// Created by egorb on 10.10.2018.
//

#include "optim/Criterion.h"

CriterionPack::CriterionPack(std::vector<std::unique_ptr<Criterion>> crits) : pack(std::move(crits)) {}

bool CriterionPack::operator()(const Track &track, size_t n) {
    bool ans = true;
    for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
        ans = (**it)(track, n) && ans;
    }
    return ans;
}
void CriterionPack::reset() {
    for (auto &crit : pack) {
        crit->reset();
    }
}

MaxN::MaxN(size_t maxN) : Criterion(), maxN(maxN) {}

bool MaxN::operator()([[maybe_unused]] const Track &track, [[maybe_unused]] size_t n) {
    return n < maxN;
}


NWithoutUpdates::NWithoutUpdates(size_t n) : Criterion(), n(n), counter(0), last_len(0) {}

bool NWithoutUpdates::operator()([[maybe_unused]] const Track &track, [[maybe_unused]] size_t nIt) {
    if (track.size() != last_len) {
        last_len = track.size();
        counter = 0;
    } else
        ++counter;
    return counter < n;
}

NWithoutUpdates::NWithoutUpdates(size_t n, size_t counter, size_t last_len) :
    n(n), counter(counter), last_len(last_len) {}

void NWithoutUpdates::reset() {
    Criterion::reset();
    counter = 0;
    last_len = 0;
}

FunctionChange::FunctionChange(double eps) : eps(eps) {}

bool FunctionChange::operator()([[maybe_unused]] const Track &track, [[maybe_unused]] size_t nIt) {
    return !(track.size() != 1 && (track[track.size() - 2].y -
        track[track.size() - 1].y) / track[track.size() - 1].y < eps);
}




