//
// Created by Alexander Krajči on 27/05/2022.
//

#include "Aplikacia.h"
#include <codecvt>
#include <fstream>
#include "iostream"
#include <sstream>

namespace structures
{
    Aplikacia::Aplikacia()
    {
        obce = new SortedSequenceTable<std::string, Obec*>;
        pomTabObce = new SortedSequenceTable<std::string, std::string>;
        nacitaj();
    }
    void Aplikacia::nacitaj()
    {
        std::ifstream loaderObci;
        std::ifstream loaderVzdelani;

        loaderVzdelani.open("../data/vzdelanie.csv");
        loaderObci.open("../data/obce.csv");

        if(!loaderVzdelani.is_open()) throw std::runtime_error("Could not open Vzdelanie.csv file");
        if(!loaderObci.is_open()) throw std::runtime_error("Could not open Obce.csv file");

        std::string lineVzd ,colNameVzd;
        std::string lineObc ,colNameObc;
        std::string vzdCode;

        int  vzd0,vzd1,vzd2,vzd3,vzd4,vzd5,vzd6,vzd7;

        std::string obcCode,obcOT,obcMT,obcST;

        std::getline(loaderVzdelani,lineVzd);
        std::getline(loaderObci,lineObc);

        int index = 0;

        while (std::getline(loaderObci, lineObc) && std::getline(loaderVzdelani,lineVzd)) {
            std::stringstream ssVzdelanie(lineVzd);
            std::stringstream ssObce(lineObc);

            std::getline(ssVzdelanie, colNameVzd, ';');

            vzdCode = colNameVzd;
            std::getline(ssVzdelanie, colNameVzd, ';');

            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd0 = std::stoi(colNameVzd);


            std::getline(ssVzdelanie, colNameVzd, ';');
            vzd1= std::stoi(colNameVzd);


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

            std::getline(ssObce,colNameObc, ';');

            std::getline(ssObce,colNameObc, ';');

            obcCode = colNameObc;

            std::getline(ssObce,colNameObc, ';');
            obcOT= colNameObc;

            std::getline(ssObce,colNameObc, ';');
            obcMT = colNameObc;

            std::getline(ssObce,colNameObc, ';');
            obcST = colNameObc;

            if (vzdCode == obcCode) {

                auto vzd = new Vzdelanie(vzd0, vzd1, vzd2, vzd3, vzd4, vzd5, vzd6, vzd7);
                auto obec = new Obec(obcCode,obcOT,obcMT,obcST, vzd);
                std::cout << obec->toString() << std::endl;

                obce->insert(obcCode, obec);

                pomTabObce->insert(obcOT, obcCode);

                std::cout << index << std::endl;

                index++;
            }
        }
        loaderObci.close();
        loaderVzdelani.close();

    }
    Aplikacia::~Aplikacia()
    {
        for (auto data : *obce)
        {
            delete data->accessData();
        }
        delete obce;
        delete pomTabObce;
    }

    Obec* Aplikacia::najdi(const std::string& nazov) {
        std::string kod =  pomTabObce->find(nazov);
        Obec* obec = obce->find(kod);
        std::cout << obec->toString() << std::endl;

        return obec;
    }
}