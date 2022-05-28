//
// Created by Alexander Krajči on 28/05/2022.
//

#include "FilterWithCriterion.h"
#pragma once

    template<typename valueType>
    class Filter_FFi : public FilterWithCriterion<valueType> {

    public:
        Filter_FFi(CriterionObec<valueType>* criterion, valueType valMin, valueType valMax) ;

    protected:
        bool passFilter(valueType val) override;

    private:
        valueType valueMax_;
        valueType valueMin_;
    };

    template<typename valueType>
    Filter_FFi<valueType>::Filter_FFi(CriterionObec<valueType>* criterion, valueType valMin, valueType valMax) :
    FilterWithCriterion<valueType>(criterion){
        valueMax_ = valMax;
        valueMin_ = valMin;
    }

    template<typename valueType>
    bool Filter_FFi<valueType>::passFilter(valueType val) {
        return val>= valueMin_ && val <= valueMax_;
    }
