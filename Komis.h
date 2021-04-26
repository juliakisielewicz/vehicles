//
// Created by kisie on 19.12.2020.
//

#ifndef KOMIS_H
#define KOMIS_H

#include <vector>
#include "Samochod.h"
#include "Motocykl.h"
#include "Rower.h"

class Komis {

    std::vector<PojazdSilnikowy*> plac;

public:
    Komis() = default;
    ~Komis();

    bool jestPusty() const { return plac.empty(); };
    static void wypisz_doOdkupienia(std::vector<Pojazd*> &lista);
    void wypisz_doSprzedania() const;
    template<typename T>
    int wybierz(std::vector<T*> &lista);
    void cenaZakupu();
    void odkup(std::vector<Pojazd*> &lista);
    void sprzedaj(std::vector<Pojazd*> &lista, std::string &kupujacy);

};

#endif //KOMIS_H
