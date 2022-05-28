//
// Created by Alexander Krajči on 28/05/2022.
//

#include "CompositeFilter.h"
#include "../UzemneJednotky/Obec.h"

#pragma once

class Filter_AND : public CompositeFilter {
    public:
        bool pass(const structures::Obec& data);

};

bool Filter_AND::pass(const structures::Obec &data) {
    bool result = true;

    for (auto filter : filters_)
    {
        result = result && filter->pass(data);
    }
    return result;
}




