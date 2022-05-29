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
        UnsortedSequenceTable<std::string, Obec*>* unsortedTable;
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


        void jednoFiltrove(bool sorting);

        void dvojfiltrove(bool sorting);

        void bezFiltrove(bool sorting);


    private:

        void volbaTriedenia(int &volba);
        void volbaFiltra(int &volba);
        void volbaKompozicie(int &volba);
        void volbaKriteria(int &volba);
        void volbaVzdelania(TypVzdelania &typ);
        void volbaZotriedenia(int &volba);
        void volbaFiltrovaniaPredTriedenim(int &volba);

        void bezFiltroveNazov(UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void bezFiltrovePocet(TypVzdelania typ,UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void bezFiltrovePodiel(TypVzdelania typ,UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void jednoFiltroveVzdelaniePocet(TypVzdelania vzdelania, UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void jednoFiltroveVzdelaniePodiel(TypVzdelania vzdelania, UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void dvojfiltrove_AND(TypVzdelania vzdPoc, TypVzdelania vzdPod, UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void dvojfiltrove_OR(TypVzdelania vzdPoc, TypVzdelania vzdPod,UnsortedSequenceTable<std::string, Obec*> &tab,bool sorting);

        void triedPodlaNazvu();

        void triedPodlaPoctu(TypVzdelania typ);

        void triedPodlaPodielu(TypVzdelania typ);

        void obnov();

    };
}