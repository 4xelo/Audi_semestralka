//
// Created by Alexander Krajči on 28/05/2022.
//
#include "../Kriterium/CriterionObecVPocet.h"
#include "FiltreSKriteriom/Filter_FFi.h"
#include "../Vzdelanie/Vzdelanie.h"
#include "../Kriterium/CriterionObecVPodiel.h"
#pragma once

class FilterObecVzdelPoc : public Filter_FFi<int> {
    public:
        FilterObecVzdelPoc(int minVal, int maxVal, TypVzdelania typ) :
                Filter_FFi<int>(new CriterionObecVPocet(typ), minVal,maxVal) {}
    };

class FilterObecVzdelPodiel : public Filter_FFi<double> {
public:
    FilterObecVzdelPodiel(double minVal, double maxVal, TypVzdelania typ) :
            Filter_FFi<double>(new CriterionObecVPodiel(typ), minVal,maxVal) {}

};


