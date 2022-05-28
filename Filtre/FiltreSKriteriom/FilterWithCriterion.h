//
// Created by Alexander Krajči on 28/05/2022.
//

#include "../../UzemneJednotky/Obec.h"
#include "../../Kriterium/CriterionObec.h"
#include "../Filter.h"
#pragma once

    template <typename valueType>
    class FilterWithCriterion : public Filter{
    public:
        explicit FilterWithCriterion(Criterion<structures::Obec, valueType>* value);
        bool pass (const structures::Obec& data) override;
        ~FilterWithCriterion() override;

    protected:
        virtual bool passFilter(valueType value) = 0;

    private:
        Criterion<structures::Obec, valueType>* criterion_;
    };

    template<typename valueType>
    FilterWithCriterion<valueType>::~FilterWithCriterion() {
        delete criterion_;
        criterion_ = nullptr;
    }

    template<typename valueType>
    bool FilterWithCriterion<valueType>::pass(const structures::Obec &data) {
        return passFilter(criterion_->evaluate(data));
    }

    template<typename valueType>
    FilterWithCriterion<valueType>::FilterWithCriterion(Criterion<structures::Obec, valueType> *value) {
        criterion_ = value;
    }







