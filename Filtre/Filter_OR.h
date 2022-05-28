//
// Created by Alexander Krajči on 28/05/2022.
//

#include "CompositeFilter.h"

#pragma once

class Filter_OR : public CompositeFilter {
    public:
      inline bool pass(const structures::Obec& data) override;
};

bool Filter_OR::pass(const structures::Obec &data) {
    bool returnValue = true;
    for (auto filter : filters_) {
        returnValue = returnValue || filter->pass(data);
    }
    return returnValue;
}
