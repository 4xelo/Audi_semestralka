//
// Created by Alexander Krajči on 28/05/2022.
//

#include "../Filter.h"
#include "list/array_list.h"
#pragma once


    class CompositeFilter: Filter {

    public:
        void registerFilter(Filter* filter);
        ~CompositeFilter();
    protected:
        structures::ArrayList<Filter*> filters_;
    };

    void CompositeFilter::registerFilter(Filter *filter) {
        filters_.add(filter);
    }

    CompositeFilter::~CompositeFilter() {
        filters_.clear();
    }





