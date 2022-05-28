//
// Created by Alexander Krajči on 28/05/2022.
//
#include "../Kriterium/Criterion.h"
#include "../UzemneJednotky/Obec.h"
#pragma once

template <typename resultType>
class CriterionObec : public Criterion<structures::Obec, resultType> {
public:
    virtual resultType evaluate(const structures::Obec &data) = 0;

};