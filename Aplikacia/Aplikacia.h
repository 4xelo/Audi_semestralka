//
// Created by Alexander Krajči on 27/05/2022.
//

#pragma once
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"
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

        void spusti();
        SortedSequenceTable<std::string, Obec*>* getObce() {return obce;}
        ~Aplikacia();

        void bodoveVyhladavanie();

        void filtrovanie();

        void triedenie();


        void jednoFiltrove();

        void dvojfiltrove();

        void bezFiltrove();


    private:

        void bezFiltrovePocet(TypVzdelania typ);

        void bezFiltrovePodiel(TypVzdelania typ);

        void jednoFiltroveVzdelaniePocet(TypVzdelania vzdelania);

        void jednoFiltroveVzdelaniePodiel(TypVzdelania vzdelania);

        void dvojfiltrove_AND(TypVzdelania vzdPoc, TypVzdelania vzdPod);

        void dvojfiltrove_OR(TypVzdelania vzdPoc, TypVzdelania vzdPod);
    };
}