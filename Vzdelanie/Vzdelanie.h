//
// Created by Alexander Krajči on 27/05/2022.
//

#pragma once

#include <string>
#include "../structures/array/array.h"
#include "../structures/list/array_list.h"
enum class TypVzdelania
{
    bez_ukonceneho = 0,
    zakladne = 1,
    ucnovske = 2,
    stredne = 3,
    vyssie =4,
    vysokoskolske = 5,
    bez_vzdelania = 6,
    nezistene = 7
};
namespace structures
{
    class Vzdelanie
    {
    private:
        Array<int>* pocetLudiVzdelanie_ = new Array<int>(8);
    public:
        Vzdelanie(int poc0,int poc1,int poc2,int poc3,int poc4,int poc5,int poc6,int poc7);

        Vzdelanie(Vzdelanie& vzd);

        Vzdelanie();
        inline int size() { return this->pocetLudiVzdelanie_->size();}

        ~Vzdelanie();
        int getPocetLudi(int index);
        void setPocetLudi(int index, int pocet);
        Vzdelanie& assign(Vzdelanie& other);
    };
}