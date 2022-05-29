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


        void bezFiltroveNazov();

        void bezFiltrovePocet(TypVzdelania typ);

        void bezFiltrovePodiel(TypVzdelania typ);

        void jednoFiltroveVzdelaniePocet_Sort(TypVzdelania vzdelania, UnsortedSequenceTable<std::string, Obec*> &tab);
        void jednoFiltroveVzdelaniePocet(TypVzdelania vzdelania);

        void jednoFiltroveVzdelaniePodiel_Sort(TypVzdelania vzdelania,UnsortedSequenceTable<std::string, Obec*> &tab);
        void jednoFiltroveVzdelaniePodiel(TypVzdelania vzdelania);


        void dvojfiltrove_AND(TypVzdelania vzdPoc, TypVzdelania vzdPod);


        void dvojfiltrove_OR(TypVzdelania vzdPoc, TypVzdelania vzdPod);

        void triedPodlaNazvu();

        void triedPodlaPoctu(TypVzdelania typ);

        void triedPodlaPodielu(TypVzdelania typ);



    };
}