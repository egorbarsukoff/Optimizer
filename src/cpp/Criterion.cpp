//
// Created by egorb on 10.10.2018.
//

#include "../Criterion.h"

CriterionPack::CriterionPack (std::vector<Criterion*> crits) : pack() {
    for (auto i : crits) {
        pack.push_back(i->copy());
    }
}

bool CriterionPack::operator() (const Track& track, size_t n) {
    bool ans = true;
    for (auto it = pack.begin(); it != pack.end() && ans; ++it) {
        ans = (**it)(track, n) && ans;
    }
    return ans;
}

std::shared_ptr<Criterion> CriterionPack::copy() const {
    std::vector<Criterion*> crPointers;
    crPointers.reserve(pack.size());
    for (auto& i : pack) {
        crPointers.push_back(i.get());
    }
    return std::shared_ptr<Criterion>(new CriterionPack(crPointers));
}


MaxN::MaxN(size_t maxN) : Criterion(), maxN(maxN) {}

bool MaxN::operator() (const Track& track, size_t n) {
    return track.size() < maxN;
}

std::shared_ptr<Criterion> MaxN::copy() const {
    return std::shared_ptr<Criterion>(new MaxN(maxN));
}


NWithoutUpdates::NWithoutUpdates(size_t n) : Criterion(), n(n), counter(0), last_len(0) {}

bool NWithoutUpdates::operator() (const Track& track, size_t nIt) {
    if (track.size() != last_len) {
        last_len = track.size();
        counter = 0;
    } else
        ++counter;
    return counter < n;
}

NWithoutUpdates::NWithoutUpdates(size_t n, size_t counter, size_t last_len) :
                                        n(n), last_len(last_len), counter(counter){}

std::shared_ptr<Criterion> NWithoutUpdates::copy() const {
    return std::shared_ptr<Criterion>(new NWithoutUpdates(n, counter, last_len));
}

void NWithoutUpdates::reset() {
    Criterion::reset();
    counter = 0;
    last_len = 0;
}

std::shared_ptr<Criterion> FunctionChange::copy() const {
    return std::shared_ptr<Criterion>(new FunctionChange(eps));
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

std::shared_ptr<Criterion> GradientCriterion::copy() const {
    return std::shared_ptr<Criterion>(new GradientCriterion(eps));
}


