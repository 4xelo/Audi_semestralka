//
// Created by Alexander Krajči on 28/05/2022.
//

#include "../Kriterium/CriterionObec.h"
#pragma once

class CriterionObecVPocet :public CriterionObec<int> {

public:
    CriterionObecVPocet(TypVzdelania typ);

    int evaluate(const structures::Obec &data);

private:
    TypVzdelania typVzdelania_;
};

    int CriterionObecVPocet::evaluate(const structures::Obec &data) {
        return data.pocetObyvSoVzdelanim(typVzdelania_);
    }

    CriterionObecVPocet::CriterionObecVPocet(TypVzdelania typ) {
        typVzdelania_ = typ;
    }

