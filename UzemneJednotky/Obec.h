//
// Created by Alexander Krajči on 27/05/2022.
//

#pragma once

#include <string>
#include "../Vzdelanie/Vzdelanie.h"
namespace structures {
    class Obec
    {
    private:

        std::string kodObce;
        std::string officialTitle;
        std::string mediumTitle;
        std::string shortTitle;
        int pocetObyvatelovObce{};
        Vzdelanie* vzdelanie;
    public:
        Obec(std::string kod, std::string ofTit, std::string meTit, std::string shTit, Vzdelanie *vzd);
        ~Obec();
        Obec(Obec& data);
        int getPocetObyvatelov();
        std::string getNazov() const;
        int pocetObyvSoVzdelanim(TypVzdelania vzd) const;
        double podielObyvSoVzdelanim(TypVzdelania vzd) const;
        std::string toString();
    };
}
