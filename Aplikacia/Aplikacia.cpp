//
// Created by Alexander Krajči on 27/05/2022.
//

#include "Aplikacia.h"
#include <codecvt>
#include <fstream>
#include "iostream"
#include "heap_sort.h"
#include "../Filtre/Filter.h"
#include "../Filtre/Filters.h"
#include "../Filtre/KompozitneFiltre/Filter_AND.h"
#include "../Filtre/KompozitneFiltre/Filter_OR.h"
#include "../Kriterium/CriterionObecNazov.h"
#include "../Kriterium/CriterionObec.h"
#include "../Kriterium/CriterionObecVPodiel.h"
#include "../Kriterium/Criterion.h"
#include <sstream>
#include <vector>
#include <random>

namespace structures {
    Aplikacia::Aplikacia() {
        obce = new SortedSequenceTable<std::string, Obec *>;
        pomTabObce = new SortedSequenceTable<std::string, std::string>;
        //unsortedTable = new UnsortedSequenceTable<std::string, Obec*>;
        nacitaj();
    }

    void Aplikacia::nacitaj() {
        std::ifstream loaderObci;
        std::ifstream loaderVzdelani;

        loaderVzdelani.open("../data/vzdelanie.csv");
        loaderObci.open("../data/obce.csv");

        if (!loaderVzdelani.is_open()) throw std::runtime_error("Could not open Vzdelanie.csv file");
        if (!loaderObci.is_open()) throw std::runtime_error("Could not open Obce.csv file");

        std::string lineVzd, colNameVzd;
        std::string lineObc, colNameObc;
        std::string vzdCode;

        int vzd0, vzd1, vzd2, vzd3, vzd4, vzd5, vzd6, vzd7;

        std::string obcCode, obcOT, obcMT, obcST;

        std::getline(loaderVzdelani, lineVzd);
        std::getline(loaderObci, lineObc);

        int index = 0;

        while (std::getline(loaderObci, lineObc) && std::getline(loaderVzdelani, lineVzd)) {
            std::stringstream ssVzdelanie(lineVzd);
            std::stringstream ssObce(lineObc);

            std::getline(ssVzdelanie, colNameVzd, ';');

            vzdCode = colNameVzd;
            std::getline(ssVzdelanie, colNameVzd, ';');

            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd0 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd1 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd2 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd3 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd4 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd5 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd6 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd7 = std::stoi(colNameVzd);

            std::getline(ssObce, colNameObc, ';');

            std::getline(ssObce, colNameObc, ';');

            obcCode = colNameObc;

            std::getline(ssObce, colNameObc, ';');
            obcOT = colNameObc;

            std::getline(ssObce, colNameObc, ';');
            obcMT = colNameObc;

            std::getline(ssObce, colNameObc, ';');
            obcST = colNameObc;

            if (vzdCode == obcCode) {
                auto vzd_1 = new Vzdelanie(vzd0, vzd1, vzd2, vzd3, vzd4, vzd5, vzd6, vzd7);
                auto obec1 = new Obec(obcCode, obcOT, obcMT, obcST, vzd_1);


                obce->insert(obcCode, obec1);


                pomTabObce->insert(obcOT, obcCode);


                index++;
            } else {
                auto vzd = new Vzdelanie(0, 0, 0, 0, 0, 0, 0, 0);
                auto obec = new Obec(obcCode, obcOT, obcMT, obcST, vzd);
                obce->insert(obcCode, obec);

                pomTabObce->insert(obcOT, obcCode);
            }
        }

        auto vzd_1 = new Vzdelanie(0, 0, 0, 0, 0, 0, 0, 0);
        auto obec1 = new Obec("SKZZZZ", "Zahraničie", "Zahraničie", "Zahraničie", vzd_1);
        obce->insert("SKZZZZ", obec1);
        pomTabObce->insert("Zahraničie", "SKZZZZ");



        auto vzd_2 = new Vzdelanie(0, 0, 0, 0, 0, 0, 0, 0);
        auto obec2 = new Obec("SKZZZZZZZZZZ", "Zahraničie1", "Zahraničie", "Zahraničie", vzd_2);
        obce->insert("SKZZZZZZZZZZ", obec2);
        pomTabObce->insert("Zahraničie1", "SKZZZZZZZZZZ");



        loaderObci.close();
        loaderVzdelani.close();

    }

    Aplikacia::~Aplikacia() {
        for (auto data: *obce) {
            delete data->accessData();
        }

        delete obce;
        obce = nullptr;

        delete pomTabObce;
    }

    Obec *Aplikacia::najdi(const std::string &nazov) {
        std::string kod = pomTabObce->find(nazov);
        Obec *obec = obce->find(kod);
        std::cout << obec->toString() << std::endl;

        return obec;
    }

    void Aplikacia::spusti() {
        std::string nazov;
        int min;
        int max;
        int volba;
        bool res;
        std::string vyber = "";

        do {
            std::cout << "\n\n-------\t\t\t\t\t\t\t\t\tSemestrálna práca\t\t\t\t\t\t\t\t\t\t-------" << std::endl;
            std::cout
                    << "------------Aplikacia na spracovanie udajov zo Scitania obyvatelov domov a bytov z roku 2021-----------"
                    << std::endl;
            std::cout
                    << "-------------------------------------------------------------------------------------------------------\n\n";

            std::cout << "1 - Bodove vyhladavanie" << std::endl;
            std::cout << "2 - Filtrovanie" << std::endl;
            std::cout << "3 - Triedenie" << std::endl;
            std::cout << "0 - Koniec\n" << std::endl;

            std::cout << "Vyber si akciu: ";

            do {
                res = false;
                std::cin >> vyber;
                volba = atoi(vyber.c_str());
                if (volba < 0 || volba >= 4) {
                    res = true;
                    std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";

                }
            } while (res);

            if (volba != 0) {
                switch (volba) {
                    case 1: {
                        bodoveVyhladavanie();
                        break;
                    }
                    case 2: {

                        filtrovanie();
                        break;
                    }

                    case 3: {
                        triedenie();
                        break;
                    }

                    default:;
                }
            }

        } while (volba != 0);

    }

    void Aplikacia::bodoveVyhladavanie() {
        std::string nazovObce;
        bool res;
        Obec *obec;
        do {
            res = false;
            std::cout << "Zadajte nazov obce ktoru chcete vyhladat: ";
            std::cin >> nazovObce;
            try {
                obec = najdi(nazovObce);
            } catch (std::logic_error) {
                obec = nullptr;
            }
            if (obec == nullptr) {
                res = true;
                std::cout << "Zadana obec sa nenasla, zadajte znova: ";
            }
        } while (res);
        CriterionObecNazov nazov;
        CriterionObecVPocet bezUkonc(TypVzdelania::bez_ukonceneho);
        CriterionObecVPocet zaklVzd(TypVzdelania::zakladne);
        CriterionObecVPocet ucnovskeVzd(TypVzdelania::ucnovske);
        CriterionObecVPocet stredneVzd(TypVzdelania::stredne);
        CriterionObecVPocet vyssieVzd(TypVzdelania::vyssie);
        CriterionObecVPocet vysokoskolske(TypVzdelania::vysokoskolske);
        CriterionObecVPocet bezVzd(TypVzdelania::bez_vzdelania);
        CriterionObecVPocet nezistene(TypVzdelania::nezistene);

        std::cout << "Nazov Obce: " << nazov.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov bez ukonceneho vzdelania: " << bezUkonc.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov so zakladnym vzdelanim: " << zaklVzd.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov s ucnovskym vzdelanim: " << ucnovskeVzd.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov so strednym vzdelanim " << stredneVzd.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov s vyssim vzdelanim: " << vyssieVzd.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov s vysokoskolskym vzdelanim: " << vysokoskolske.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov bez vzdelania: " << bezVzd.evaluate(*obec) << std::endl;
        std::cout << "Pocet obyvatelov s nezistenym vzdelanim: " << nezistene.evaluate(*obec) << std::endl;

    }

    void Aplikacia::filtrovanie() {
        bool res;
        bool sorting = false;
        std::string vyber;
        int volbaFiltra;
        this->volbaFiltra(volbaFiltra);
        switch (volbaFiltra) {
            case 1: {
                jednoFiltrove(sorting);
                break;
            }
            case 2: {
                dvojfiltrove(sorting);
                break;
            }
            default:
                bezFiltrove(sorting);

        }
    }

    void Aplikacia::bezFiltrove(bool sorting) {
        bool res;
        bool need = sorting;
        std::string vyber;
        int volbaKriteria;
        int volbaVzdelania = 0;
        this->volbaKriteria(volbaKriteria);

        TypVzdelania typ;
        if (volbaKriteria != 3) {
            this->volbaVzdelania(typ);
        }

        switch (volbaKriteria) {
            case 1:
                bezFiltrovePocet(typ);
                break;
            case 2:
                bezFiltrovePodiel(typ);
                break;
            default:
                bezFiltroveNazov();
        }
    }

    void Aplikacia::bezFiltroveNazov() {
        CriterionObecNazov nazov;
        for (auto data : *obce) {
            std::cout << nazov.evaluate(*data->accessData()) << std::endl;
        }
    }


    void Aplikacia::bezFiltrovePocet(TypVzdelania typ) {
        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(typ);

        for (auto data : *obce) {
            std::cout << nazov.evaluate(*data->accessData()) << " || "
                      << vzdelPocet.evaluate(*data->accessData()) << std::endl;

        }
    }


    void Aplikacia::bezFiltrovePodiel(TypVzdelania typ) {
        CriterionObecNazov nazov;
        CriterionObecVPodiel cVzdelPodiel(typ);
        for (auto data : *obce) {
            std::cout << nazov.evaluate(*data->accessData()) << " || "
                      << cVzdelPodiel.evaluate(*data->accessData()) << std::endl;
        }
    }


    void Aplikacia::jednoFiltrove(bool sorting) {
        bool res;
        std::string vyber;
        int volbaFiltra;
        int volbaVzdelania;
        bool need = sorting;
        do {
            res = false;
            std::cout << "Zvolte si filter, ktorym budete filtrovat: " << std::endl;
            std::cout << "1 - F-Vzdelanie Pocet" << std::endl;
            std::cout << "2 - F-Vzdelanie Podiel" << std::endl;
            std::cin >> vyber;
            volbaFiltra = atoi(vyber.c_str());
            if (volbaFiltra <= 0 || volbaFiltra >= 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }
        } while (res);

        TypVzdelania typ;
        this->volbaVzdelania(typ);

        if (volbaFiltra == 1) {
            jednoFiltroveVzdelaniePocet(typ);
        }else {
            jednoFiltroveVzdelaniePodiel(typ);
        }

    }

    void Aplikacia::jednoFiltroveVzdelaniePocet_Sort(TypVzdelania vzdelanie,
                                                     UnsortedSequenceTable<std::string, Obec *> &tab) {
        int min;
        int max;
        std::string minStr;
        std::string maxStr;
        std::cout << "Zadaj spodnu hranicu intervalu" << std::endl;
        std::cin >> minStr;
        min = atoi(minStr.c_str());

        std::cout << "Zadaj hornu hranicu intervalu"<< std::endl;
        std::cin >> maxStr;
        max = atoi(maxStr.c_str());

        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(vzdelanie);
        FilterObecVzdelPoc vzdelPoc(min,max,vzdelanie);

        tab.clear();
        for (auto data : *obce) {
            if (vzdelPoc.pass(*data->accessData())) {
                tab.insert(data->getKey(), new Obec(*data->accessData()));
            }
        }
    }

    void Aplikacia::jednoFiltroveVzdelaniePocet(TypVzdelania vzdelanie) {
        int min;
        int max;
        std::string minStr;
        std::string maxStr;
        std::cout << "Zadaj spodnu hranicu intervalu" << std::endl;
        std::cin >> minStr;
        min = atoi(minStr.c_str());

        std::cout << "Zadaj hornu hranicu intervalu"<< std::endl;
        std::cin >> maxStr;
        max = atoi(maxStr.c_str());

        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(vzdelanie);
        FilterObecVzdelPoc vzdelPoc(min,max,vzdelanie);

        for (auto data : *obce) {
            if (vzdelPoc.pass(*data->accessData())) {
                std::cout << nazov.evaluate(*data->accessData()) << " || "
                          << vzdelPocet.evaluate(*data->accessData()) << std::endl;
            }
        }
    }

    void Aplikacia::jednoFiltroveVzdelaniePodiel_Sort(TypVzdelania vzdelanie,
                                                      UnsortedSequenceTable<std::string, Obec *> &tab) {
        double min;
        double max;
        std::string minStr;
        std::string maxStr;
        std::cout << "Zadaj spodnu hranicu intervalu v tvare (0.12)" << std::endl;//4,15,61
        std::cin.ignore();
        getline(std::cin,minStr);
        min = std::stod(minStr);

        std::cout << "Zadaj hornu hranicu intervalu v tvare (0.12)"<< std::endl;
        std::cin.ignore();
        getline(std::cin, maxStr);
        max = std::stod(maxStr);

        CriterionObecNazov nazov;
        CriterionObecVPodiel cVzdelPodiel(vzdelanie);
        FilterObecVzdelPodiel fVzdelPodiel(min,max,vzdelanie);

        tab.clear();
        for (auto data: *obce) {
            if (fVzdelPodiel.pass(*data->accessData())) {
                tab.insert(data->getKey(), new Obec(*data->accessData()));
            }
        }
    }

    void Aplikacia::jednoFiltroveVzdelaniePodiel(TypVzdelania vzdelanie) {
        double min;
        double max;
        std::string minStr;
        std::string maxStr;
        std::cout << "Zadaj spodnu hranicu intervalu v tvare (0.12)" << std::endl;//4,15,61
        std::cin.ignore();
        getline(std::cin,minStr);
        min = std::stod(minStr);

        std::cout << "Zadaj hornu hranicu intervalu v tvare (0.12)"<< std::endl;
        std::cin.ignore();
        getline(std::cin, maxStr);
        max = std::stod(maxStr);

        CriterionObecNazov nazov;
        CriterionObecVPodiel cVzdelPodiel(vzdelanie);
        FilterObecVzdelPodiel fVzdelPodiel(min,max,vzdelanie);

        for (auto data : *obce) {
            if (fVzdelPodiel.pass(*data->accessData())) {
                std::cout << nazov.evaluate(*data->accessData()) << " || "
                          << cVzdelPodiel.evaluate(*data->accessData()) << std::endl;

            }
        }
    }

    void Aplikacia::dvojfiltrove(bool sorting) {
        bool need = sorting;
        int volbaKompozicie;
        TypVzdelania typPocet;
        this->volbaVzdelania(typPocet);

        TypVzdelania typPodiel;
        this->volbaVzdelania(typPodiel);

        this->volbaKompozicie(volbaKompozicie);

        if (volbaKompozicie == 1) {
            dvojfiltrove_AND(typPocet, typPodiel);
        } else {
            dvojfiltrove_OR(typPocet,typPodiel);
        }
    }

    void Aplikacia::dvojfiltrove_AND(TypVzdelania vzdPoc, TypVzdelania vzdPod) {

        int minPoc;
        int maxPoc;
        std::string minStrPoc;
        std::string maxStrPoc;
        double minPod;
        double maxPod;
        std::string minStrPod;
        std::string maxStrPod;

        std::cout << "Zadaj spodnu hranicu intervalu pre filter Vzdelanie Pocet" << std::endl;
        std::cin >> minStrPoc;
        minPoc = atoi(minStrPoc.c_str());

        std::cout << "Zadaj hornu hranicu intervalu pre filter Vzdelanie Pocet"<< std::endl;
        std::cin >> maxStrPoc;
        maxPoc = atoi(maxStrPoc.c_str());

        std::cout << "Zadaj spodnu hranicu intervalu pre filter Vzdelanie Podiel v tvare (0.12)" << std::endl;
        std::cin.ignore();
        getline(std::cin,minStrPod);
        minPod = std::stod(minStrPod);

        std::cout << "Zadaj hornu hranicu intervalu pre filter Vzdelanie Podiel v tvare (0.12)" << std::endl;
        std::cin.ignore();
        getline(std::cin,maxStrPod);
        maxPod = std::stod(maxStrPod);


        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(vzdPoc);
        CriterionObecVPodiel vzdelPodiel(vzdPod);

        FilterObecVzdelPoc filterVzdelPocet(minPoc,maxPoc,vzdPoc);
        FilterObecVzdelPodiel filterVzdelPodiel(minPod,maxPod,vzdPod);
        Filter_AND filterAnd;
        filterAnd.registerFilter(&filterVzdelPocet);
        filterAnd.registerFilter(&filterVzdelPodiel);

        std::cout << "\n\t\t\t\tFilrovanie"<< std::endl;

        for (auto data: *obce) {
                if (filterAnd.pass(*data->accessData())) {
                    std::cout << nazov.evaluate(*data->accessData()) << " || "
                              << vzdelPocet.evaluate(*data->accessData()) << " || "
                              << vzdelPodiel.evaluate(*data->accessData()) << std::endl;
                }
        }

    }



    void Aplikacia::dvojfiltrove_OR(TypVzdelania vzdPoc, TypVzdelania vzdPod) {
        int minPoc;
        int maxPoc;
        std::string minStrPoc;
        std::string maxStrPoc;
        double minPod;
        double maxPod;
        std::string minStrPod;
        std::string maxStrPod;

        std::cout << "Zadaj spodnu hranicu intervalu pre filter Vzdelanie Pocet" << std::endl;
        std::cin >> minStrPoc;
        minPoc = atoi(minStrPoc.c_str());

        std::cout << "Zadaj hornu hranicu intervalu pre filter Vzdelanie Pocet" << std::endl;
        std::cin >> maxStrPoc;
        maxPoc = atoi(maxStrPoc.c_str());

        std::cout << "Zadaj spodnu hranicu intervalu pre filter Vzdelanie Podiel z intervalu (0.1 - 0.99)" << std::endl;
        std::cin.ignore();
        getline(std::cin, minStrPod);
        minPod = std::stod(minStrPod);

        std::cout << "Zadaj hornu hranicu intervalu pre filter Vzdelanie Podiel v tvare (0.1 - 0.99)" << std::endl;
        std::cin.ignore();
        getline(std::cin, maxStrPod);
        maxPod = std::stod(maxStrPod);

        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(vzdPoc);
        CriterionObecVPodiel vzdelPodiel(vzdPod);

        FilterObecVzdelPoc filterVzdelPocet(minPoc, maxPoc, vzdPoc);
        FilterObecVzdelPodiel filterVzdelPodiel(minPod, maxPod, vzdPod);
        Filter_OR filterOr;
        filterOr.registerFilter(&filterVzdelPocet);
        filterOr.registerFilter(&filterVzdelPodiel);
        std::cout << "\n\t\t\t\tFilrovanie" << std::endl;


        for (auto data: *obce)
        {
            if (filterOr.pass(*data->accessData()))
            {
                std::cout << nazov.evaluate(*data->accessData()) << " || "
                << vzdelPocet.evaluate(*data->accessData()) << " || "
                << vzdelPodiel.evaluate(*data->accessData()) << std::endl;
            }
        }

    }

    void Aplikacia::triedenie() {

        int volbaTriedenia;
        this->volbaTriedenia(volbaTriedenia);
        TypVzdelania typ;

        if (volbaTriedenia != 1) {
            this->volbaVzdelania(typ);
        }
        switch (volbaTriedenia) {
            case 1:
                triedPodlaNazvu();
                break;
            case 2:
                triedPodlaPoctu(typ);
                break;
            default:
                triedPodlaPodielu(typ);
        }
    }

    void Aplikacia::triedPodlaNazvu(){
        int volbaTriedenia;
        auto sorterString = new structures::HeapSort<std::string,structures::Obec*,std::string>;
        auto unsTable = new UnsortedSequenceTable<std::string, Obec*>;
        CriterionObecNazov nazov;
        this->volbaZotriedenia(volbaTriedenia);

        for (auto data : *obce) {
            unsTable->insert(data->getKey(),new Obec(*data->accessData()));
        }

        if (volbaTriedenia == 1) {
            sorterString->sortWithCriterion(*unsTable,true,nazov);
        } else {
            sorterString->sortWithCriterion(*unsTable, false,nazov);
        }

        for (auto data : *unsTable) {
            std::cout << nazov.evaluate(*data->accessData()) << std::endl;
        }

        delete sorterString;
        for (auto item : *unsTable) {
            delete item->accessData();
        }
        delete unsTable;
        unsTable = nullptr;
    }

    void Aplikacia::triedPodlaPoctu(TypVzdelania typ) {
        int volbaFiltrovaniaPredTriedenim;
        int volbaZotriedenia;
        auto unsTable = new UnsortedSequenceTable<std::string, Obec*>;
        auto sorterInt = new structures::HeapSort<std::string,structures::Obec*,int>;
        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(typ);
        this->volbaFiltrovaniaPredTriedenim(volbaFiltrovaniaPredTriedenim);

        if (volbaFiltrovaniaPredTriedenim == 1) {

            jednoFiltroveVzdelaniePocet_Sort(typ,*unsTable);

            this->volbaZotriedenia(volbaZotriedenia);
            if (volbaZotriedenia == 1) {
                sorterInt->sortWithCriterion(*unsTable,true,vzdelPocet);
            } else {
                sorterInt->sortWithCriterion(*unsTable, false,vzdelPocet);
            }
        }
        else {
            this->volbaZotriedenia(volbaZotriedenia);
            if (volbaZotriedenia == 1) {
                sorterInt->sortWithCriterion(*unsTable,true,vzdelPocet);
            } else {
                sorterInt->sortWithCriterion(*unsTable, false,vzdelPocet);
            }
        }

        for (auto data : *unsTable) {
            std::cout << nazov.evaluate(*data->accessData()) << " " <<
                      vzdelPocet.evaluate(*data->accessData()) << std::endl;
        }
        delete sorterInt;

        for (auto item : *unsTable) {
            delete item->accessData();
        }
        delete unsTable;

        unsTable = nullptr;

    }

    void Aplikacia::triedPodlaPodielu(TypVzdelania typ) {
        auto sorterDouble = new structures::HeapSort<std::string,structures::Obec*,double>;
        int volbaFiltrovaniaPredTriedenim;
        int volbaZotriedenia;
        auto unsTable = new UnsortedSequenceTable<std::string, Obec*>;

        CriterionObecNazov nazov;
        CriterionObecVPodiel vzdelPodiel(typ);
        this->volbaFiltrovaniaPredTriedenim(volbaFiltrovaniaPredTriedenim);

        if (volbaFiltrovaniaPredTriedenim == 1) {
            jednoFiltroveVzdelaniePodiel_Sort(typ,*unsTable);

            this->volbaZotriedenia(volbaZotriedenia);
            if (volbaZotriedenia == 1) {
                sorterDouble->sortWithCriterion(*unsTable,true,vzdelPodiel);
            } else {
                sorterDouble->sortWithCriterion(*unsTable, false,vzdelPodiel);
            }
        }
        else {
            this->volbaZotriedenia(volbaZotriedenia);
            if (volbaZotriedenia == 1) {
                sorterDouble->sortWithCriterion(*unsTable,true,vzdelPodiel);
            } else {
                sorterDouble->sortWithCriterion(*unsTable, false,vzdelPodiel);
            }
        }

        for (auto data : *unsTable) {
            std::cout << nazov.evaluate(*data->accessData()) << " " <<
                      vzdelPodiel.evaluate(*data->accessData()) << std::endl;
             }

        for (auto item : *unsTable) {
            delete item->accessData();
        }
        delete unsTable;
        unsTable = nullptr;
        delete sorterDouble;
    }
    void Aplikacia::volbaKriteria(int &volba) {
        bool res;
        std::string vyber;
        do {
            res = false;
            std::cout << "Zvolte si kriterium, ktore chcete vypisat: " << std::endl;
            std::cout << "1 - Vzdelanie Pocet" << std::endl;
            std::cout << "2 - Vzdelanie Podiel" << std::endl;
            std::cout << "3 - Nazov" << std::endl;

            std::cin >> vyber;
            volba = atoi(vyber.c_str());
            if (volba <= 0 || volba > 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }

        } while (res);

    }

    void Aplikacia::volbaVzdelania(TypVzdelania &typ) {
        bool res;
        int volbaVzdelania;
        std::string vyber;
        do {
            res = false;
            std::cout << "Zvol si aky typ vzdelania bude filtrovat filter vzdelanie Pocet: " << std::endl;
            std::cout << "0 - Bez ukonceneho vzdelania" << std::endl;
            std::cout << "1 - Zakladne vzdelanie" << std::endl;
            std::cout << "2 - Ucnovske vzdelanie" << std::endl;
            std::cout << "3 - Stredne vzdelanie" << std::endl;
            std::cout << "4 - Vyssie vzdelanie" << std::endl;
            std::cout << "5- Vysokoskolske vzdelanie" << std::endl;
            std::cout << "6 - Bez vzdelania" << std::endl;
            std::cout << "7 - Nezistene" << std::endl;
            std::cin >> vyber;
            volbaVzdelania = atoi(vyber.c_str());
            if (volbaVzdelania < 0 || volbaVzdelania > 7) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }
        } while (res);

        switch (volbaVzdelania) {
            case 0:
                typ = TypVzdelania::bez_ukonceneho;
                break;
            case 1:
                typ = TypVzdelania::zakladne;
                break;
            case 2:
                typ = TypVzdelania::ucnovske;
                break;
            case 3:
                typ = TypVzdelania::stredne;
                break;
            case 4:
                typ = TypVzdelania::vyssie;
                break;
            case 5:
                typ = TypVzdelania::vysokoskolske;
                break;
            case 6:
                typ = TypVzdelania::bez_vzdelania;
                break;
            default:
                typ = TypVzdelania::nezistene;
        }
    }

    void Aplikacia::volbaZotriedenia(int &volba) {
        bool res;
        std::string vyberTriedenia;
        do {
            res = false;
            std::cout << "Ako chcete usporiadat nazvy: " << std::endl;
            std::cout << " 1 - Vzostupne" << std::endl;
            std::cout << " 2 - Zostupne" << std::endl;
            std::cin >> vyberTriedenia ;
            volba = atoi(vyberTriedenia.c_str());
            if (volba <= 0 || volba >= 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: " << std::endl;
            }
        }
        while(res);
    }

    void Aplikacia::volbaKompozicie(int &volba) {
        bool res;
        std::string vyber;
        do {
            res = false;
            std::cout << "Chcete vyfiltrovat prienik filtrov alebo zjednotenie? :" << std::endl;
            std::cout << " 1 - Prienik" << std::endl;
            std::cout << " 2 - Zjednotenie" << std::endl;
            std::cin >> vyber;
            volba = atoi(vyber.c_str());
            if (volba <= 0 || volba >= 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }
        } while (res);
    }

    void Aplikacia::volbaFiltra(int &volba) {
        bool res;
        std::string vyber;
        do {
            res = false;
            std::cout << "Zvolte si kolko filtrov budete pouzivat: " << std::endl;
            std::cout << "1 - 1 filter " << std::endl;
            std::cout << "2 - 2 filtre" << std::endl;
            std::cout << "3 - Bez filtra" << std::endl;
            std::cin >> vyber;
            volba = atoi(vyber.c_str());
            if (volba <= 0 || volba >= 4) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }
        } while (res);
    }

    void Aplikacia::volbaTriedenia(int &volba) {
        bool res;
        std::string vyberTriedenia;
        do {
            res = false;
            std::cout << "Vyberte si ako chcete triedit: " << std::endl;
            std::cout << " 1 - Podla nazvu " << std::endl;
            std::cout << " 2 - Podla poctu vzdelania " << std::endl;
            std::cout << " 3 - Podla podielu vzdelania " << std::endl;
            std::cin >> vyberTriedenia;
            volba = atoi(vyberTriedenia.c_str());
            if (volba <= 0 || volba >= 4) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: " << std::endl;
            }

        }while (res);
    }

    void Aplikacia::volbaFiltrovaniaPredTriedenim(int &volba) {
        bool res;
        std::string vyber;

        do {
            res = false;
            std::cout << "Chcete uplatnit filtrovanie pred triedenim? :" <<std::endl;
            std::cout << " 1 - Ano" << std::endl;
            std::cout << " 2 - Nie" << std::endl;
            std::cin >> vyber;
            volba = atoi(vyber.c_str());
            if (volba <= 0 || volba >=3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: " << std::endl;
            }
        }while (res);
    }


}


