//
// Created by Alexander Krajči on 28/05/2022.
//


#include "../Kriterium/CriterionObec.h"
#include "CriterionObecNazov.h"

#pragma once

class CriterionObecVPodiel : public CriterionObec<double> {
public:
    CriterionObecVPodiel(TypVzdelania typ);
    double evaluate(const structures::Obec& data) override ;
private:
    TypVzdelania typVzdelania_;
};

double CriterionObecVPodiel::evaluate(const structures::Obec &data) {
    return data.podielObyvSoVzdelanim(typVzdelania_);
}

CriterionObecVPodiel::CriterionObecVPodiel(TypVzdelania typ) {
    typVzdelania_ = typ;
}
