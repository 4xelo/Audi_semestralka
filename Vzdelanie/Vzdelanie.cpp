//
// Created by Alexander Krajči on 27/05/2022.
//

#include "Vzdelanie.h"
namespace structures
{

    int Vzdelanie::getPocetLudi(int index)
    {
        return pocetLudiVzdelanie_->at(index);
    }
    void Vzdelanie::setPocetLudi(int index, int pocet)
    {
        pocetLudiVzdelanie_->at(index) = pocet;
    }

    Vzdelanie& Vzdelanie::assign(Vzdelanie& other)
    {

        delete pocetLudiVzdelanie_;

        pocetLudiVzdelanie_ = new Array<int>(*other.pocetLudiVzdelanie_);
        return *this;
    }

    Vzdelanie::~Vzdelanie() {
        delete pocetLudiVzdelanie_;
        pocetLudiVzdelanie_ = nullptr;
    }

    Vzdelanie::Vzdelanie(int poc0,int poc1,int poc2,int poc3, int poc4, int poc5, int poc6, int poc7) {
        pocetLudiVzdelanie_->at(0) = poc0;
        pocetLudiVzdelanie_->at(1) = poc1;
        pocetLudiVzdelanie_->at(2) = poc2;
        pocetLudiVzdelanie_->at(3) = poc3;
        pocetLudiVzdelanie_->at(4) = poc4;
        pocetLudiVzdelanie_->at(5) = poc5;
        pocetLudiVzdelanie_->at(6) = poc6;
        pocetLudiVzdelanie_->at(7) = poc7;
    }

    Vzdelanie::Vzdelanie(Vzdelanie& vzd)

    {
        pocetLudiVzdelanie_->assign(*vzd.pocetLudiVzdelanie_);
    }

    Vzdelanie::Vzdelanie() {

    }
}