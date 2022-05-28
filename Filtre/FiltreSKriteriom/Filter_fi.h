//
// Created by Alexander Krajči on 28/05/2022.
//

#include "FilterWithCriterion.h"
#pragma once


    template<typename valueType>
    class Filter_fi: public FilterWithCriterion<valueType> {

    public:
        Filter_fi(CriterionObec<valueType>* criterion, valueType val);
    protected:
        bool passFilter(valueType val) override;

    private:
        valueType value_;
    };

    template<typename valueType>
    Filter_fi<valueType>::Filter_fi(CriterionObec<valueType>* criterion, valueType val) :
            FilterWithCriterion<valueType>(criterion)
    {
        value_ = val;
    }

    template<typename valueType>
    bool Filter_fi<valueType>::passFilter(valueType val) {
        return value_ == val;
    }

