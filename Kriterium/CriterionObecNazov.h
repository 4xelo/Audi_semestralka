//
// Created by Alexander Krajči on 28/05/2022.
//
#include "../Kriterium/CriterionObec.h"

#pragma once

class CriterionObecNazov :public CriterionObec<std::string> {

public:
    std::string evaluate(const structures::Obec& data) override;
};

    std::string CriterionObecNazov::evaluate(const structures::Obec &data) {

        return data.getNazov();

    }


