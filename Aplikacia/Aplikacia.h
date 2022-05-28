//
// Created by Alexander Krajči on 27/05/2022.
//

#pragma once
#include "../structures/table/sorted_sequence_table.h"

#include "../UzemneJednotky/Obec.h"

namespace structures
{
    class Aplikacia
    {
    private:
        SortedSequenceTable<std::string, Obec*>* obce;
        SortedSequenceTable<std::string, std::string>* pomTabObce;
    public:
        Aplikacia();
        void nacitaj();
        Obec* najdi(const std::string&);

        SortedSequenceTable<std::string, Obec*>* getObce() {return obce;}

        ~Aplikacia();
    };
}