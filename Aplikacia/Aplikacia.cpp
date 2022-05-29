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

                auto vzd = new Vzdelanie(vzd0, vzd1, vzd2, vzd3, vzd4, vzd5, vzd6, vzd7);
                auto obec = new Obec(obcCode, obcOT, obcMT, obcST, vzd);

                obce->insert(obcCode, obec);

                pomTabObce->insert(obcOT, obcCode);

                index++;
            } else {
                auto vzd = new Vzdelanie(0, 0, 0, 0, 0, 0, 0, 0);
                auto obec = new Obec(obcCode, obcOT, obcMT, obcST, vzd);
                obce->insert(obcCode, obec);

                pomTabObce->insert(obcOT, obcCode);
            }
        }

        /*auto vzd = new Vzdelanie(0, 0, 0, 0, 0, 0, 0, 0);
        auto obec = new Obec("SKZZZZ", "Zahraničie", "Zahraničie", "Zahraničie", vzd);
        obce->insert("SKZZZZ", obec);
        pomTabObce->insert("Zahraničie", "SKZZZZ");
        auto obec2 = new Obec("SKZZZZZZZZZZ", "Zahraničie1", "Zahraničie", "Zahraničie", vzd);
        obce->insert("SKZZZZZZZZZZ", obec2);
        pomTabObce->insert("Zahraničie1", "SKZZZZZZZZZZ");*/


        loaderObci.close();
        loaderVzdelani.close();

    }

    Aplikacia::~Aplikacia() {
        for (auto data: *obce) {
            delete data->accessData();
        }
        delete obce;
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
        auto *unsTab = new UnsortedSequenceTable<std::string, Obec *>;

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


//        structures::Obec* obec = najdi("Trnava");
//
//
//
//        int pocetLudi = obec->pocetObyvSoVzdelanim(TypVzdelania::vysokoskolske);
//        double podielLudi = obec->podielObyvSoVzdelanim(TypVzdelania::vysokoskolske);
//
//        FilterObecVzdelPoc vzdelPoc(350,400,TypVzdelania::vysokoskolske);
//
//        CriterionObecVPocet vzd(TypVzdelania::vysokoskolske);
//        CriterionObecNazov nazov;
//
//        Filter_OR fOr;
//        fOr.registerFilter(&vzdelPoc);
//
//        auto* unsTab = new structures::UnsortedSequenceTable<std::string, structures::Obec*>;
//
//
//        for (auto data : *obce) {
//            if (vzdelPoc.pass(*data->accessData())) {
//
//                unsTab->insert(data->getKey(),data->accessData());
//                std::cout << nazov.evaluate(*data->accessData()) << " " <<  std::endl;
//                std::cout << vzd.evaluate(*data->accessData()) << std::endl;
//            }
//        }
//
//        std::cout << std::endl;
        //  auto sorterInt = new structures::HeapSort<std::string,structures::Obec*,int>;
//        auto sorterDouble = new structures::HeapSort<std::string,structures::Obec*,double>;
//        auto sorterString = new structures::HeapSort<std::string,structures::Obec*,std::string>;
//
        //         sorterInt->sortWithCriterion(*unsTab, true,vzd);
//
//        for (auto item : *unsTab) {
//            std::cout  << vzd.evaluate(*item->accessData()) << std::endl;
//        }
//
//

        delete unsTab;
//        delete sorterInt;
//        delete sorterDouble;
//        delete sorterString;
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
        std::string vyber;
        int volba;
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

        switch (volba) {
            case 1: {
                jednoFiltrove();
                break;
            }
            case 2: {
                dvojfiltrove();
                break;
            }
            default:
                bezFiltrove();
                break;

        }
    }

    void Aplikacia::jednoFiltrove() {
        bool res;
        std::string vyber;
        int volbaFiltra;
        int volbaVzdelania;
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
        typ = vyberVzdelanie(res, volbaVzdelania);

        if (volbaFiltra == 1) {
            jednoFiltroveVzdelaniePocet(typ);
        }else {
            jednoFiltroveVzdelaniePodiel(typ);
        }

    }
    void Aplikacia::dvojfiltrove() {
        bool res = false;
        std::string vyber;
        int volbaVzdelaniaFPocet;
        int volbaVzdelaniaFPodiel;

        int volbaKompozicie;
        TypVzdelania typPocet;
        typPocet = vyberVzdelanie(res,volbaVzdelaniaFPocet);

        TypVzdelania typPodiel;
        typPodiel = vyberVzdelanie(res,volbaVzdelaniaFPodiel);

        do {
            res = false;
            std::cout << "Chcete vyfiltrovat prienik filtrov alebo zjednotenie? :" << std::endl;
            std::cout << " 1 - Prienik" << std::endl;
            std::cout << " 2 - Zjednotenie" << std::endl;
            std::cin >> vyber;
            volbaKompozicie = atoi(vyber.c_str());
            if (volbaKompozicie <= 0 || volbaKompozicie >= 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }
        } while (res);
        if (volbaKompozicie == 1) {
            dvojfiltrove_AND(typPocet, typPodiel);
        } else {
            dvojfiltrove_OR(typPocet,typPodiel);
        }
    }

    void Aplikacia::bezFiltrove() {
        bool res;
        std::string vyber;
        int volbaKriteria;
        int volbaVzdelania = 0;
        do {
            res = false;
            std::cout << "Zvolte si kriterium, ktore chcete vypisat: " << std::endl;
            std::cout << "1 - Vzdelanie Pocet" << std::endl;
            std::cout << "2 - Vzdelanie Podiel" << std::endl;
            std::cin >> vyber;
            volbaKriteria = atoi(vyber.c_str());
            if (volbaKriteria <= 0 || volbaKriteria >= 3) {
                res = true;
                std::cout << "Bola zadana zla hodnota, prosim zopakujte vyber: ";
            }

        }
        while(res);
        TypVzdelania typ;
         typ = vyberVzdelanie(res,volbaVzdelania);


        if (volbaKriteria == 1) {
            bezFiltrovePocet(typ);

        } else {
            bezFiltrovePodiel(typ);
      }
    }

    void Aplikacia::jednoFiltroveVzdelaniePocet(TypVzdelania typVzdelania) {
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
        CriterionObecVPocet vzdelPocet(typVzdelania);
        FilterObecVzdelPoc vzdelPoc(min,max,typVzdelania);

        for (auto data : *obce) {
            if (vzdelPoc.pass(*data->accessData())) {

                std::cout << nazov.evaluate(*data->accessData()) << " "
                << vzdelPocet.evaluate(*data->accessData()) << std::endl;
            }
        }

    }

    void Aplikacia::jednoFiltroveVzdelaniePodiel(TypVzdelania typVzdelania) {
        double min;
        double max;
        std::string minStr;
        std::string maxStr;
        std::cout << "Zadaj spodnu hranicu intervalu v tvare (0.12)" << std::endl;
        std::cin.ignore();
        getline(std::cin,minStr);
        min = std::stod(minStr);

        std::cout << "Zadaj hornu hranicu intervalu v tvare (0.12)"<< std::endl;
        std::cin.ignore();
        getline(std::cin, maxStr);
        max = std::stod(maxStr);

        CriterionObecNazov nazov;
        CriterionObecVPodiel cVzdelPodiel(typVzdelania);
        FilterObecVzdelPodiel fVzdelPodiel(min,max,typVzdelania);

        for (auto data : *obce) {
            if (fVzdelPodiel.pass(*data->accessData())) {

                std::cout << nazov.evaluate(*data->accessData()) << " "
                          << cVzdelPodiel.evaluate(*data->accessData()) << std::endl;
            }
        }
    }

    void Aplikacia::triedenie() {

    }

    void Aplikacia::bezFiltrovePocet(TypVzdelania typ) {
        CriterionObecNazov nazov;
        CriterionObecVPocet vzdelPocet(typ);

        for (auto data : *obce) {

            std::cout << nazov.evaluate(*data->accessData()) << " "
            << vzdelPocet.evaluate(*data->accessData()) << std::endl;
        }
    }

    void Aplikacia::bezFiltrovePodiel(TypVzdelania typ) {
        CriterionObecNazov nazov;
        CriterionObecVPodiel cVzdelPodiel(typ);

        for (auto data : *obce) {

            std::cout << nazov.evaluate(*data->accessData()) << " "
                      << cVzdelPodiel.evaluate(*data->accessData()) << std::endl;

        }
    }



    TypVzdelania Aplikacia::vyberVzdelanie(bool res, int volbaVzdelania) {
        std::string vyber;
        do {
            res = false;
            std::cout << "Zvol si podla akeho typu vzdelania budes filtrovat: " << std::endl;
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

        TypVzdelania typ;

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


                return typ;
        }
    }

    void Aplikacia::dvojfiltrove_AND(TypVzdelania vzdPoc, TypVzdelania vzdPod) {

    }

    void Aplikacia::dvojfiltrove_OR(TypVzdelania vzdPoc, TypVzdelania vzdPod) {

    }
}


