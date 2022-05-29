//
// Created by Alexander Krajči on 27/05/2022.
//

#include "Obec.h"
#include <utility>
#include <iostream>

namespace  structures
{

    Obec::Obec(std::string kod, std::string ofTit, std::string meTit, std::string shTit, Vzdelanie *vzd)
    {
        kodObce = std::move(kod);
        officialTitle = std::move(ofTit);
        mediumTitle = std::move(meTit);
        shortTitle = std::move(shTit);
        vzdelanie = vzd;
        pocetObyvatelovObce = getPocetObyvatelov();

    }

    int Obec::getPocetObyvatelov() {
        int value = 0;
        for (int i = 0; i < vzdelanie->size(); ++i) {
            value += vzdelanie->getPocetLudi(i);
        }
        return value;
    }

    Obec::~Obec() {
        kodObce = "";
        officialTitle = "";
        mediumTitle = "";
        shortTitle = "";
        pocetObyvatelovObce = 0;
        delete vzdelanie;
        vzdelanie = nullptr;

    }

    std::string Obec::toString() {
        std::string result;
        result += kodObce + " " + officialTitle + " " + mediumTitle + " " + shortTitle + " " + std::to_string(pocetObyvatelovObce);
        return result;
    }

    std::string Obec::getNazov() const {
        return officialTitle;
    }

    int Obec::pocetObyvSoVzdelanim(TypVzdelania typ) const{
        int index = static_cast<int>(typ);
        return vzdelanie->getPocetLudi(index);
    }

    double Obec::podielObyvSoVzdelanim(TypVzdelania typ) const {
        int index = static_cast<int>(typ);
        double result;
        if (pocetObyvatelovObce != 0) {
             result = (double)vzdelanie->getPocetLudi(index) / pocetObyvatelovObce;
        } else {
            result = (double)vzdelanie->getPocetLudi(index) / 1;
        }

        return result;
    }

    Obec::Obec(Obec& data):
    officialTitle(data.officialTitle), pocetObyvatelovObce(data.pocetObyvatelovObce), vzdelanie(new Vzdelanie(*data.vzdelanie)),
    mediumTitle(data.mediumTitle), shortTitle(data.shortTitle)
    {

    }
}