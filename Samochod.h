//
// Created by kisie on 12.12.2020.
//

#ifndef SAMOCHOD_H
#define SAMOCHOD_H

#include "PojazdSilnikowy.h"

class Samochod : public PojazdSilnikowy {

    int liczba_drzwi;

public:

    Samochod(double spal, int lad, double c, std::string kol = "", int ld = 0);
    void tankuj(double litry) override;
    void p_wypisz(int indeks) const override;

    friend class Fabryka;
    friend class Komis;
};

#endif //SAMOCHOD_H
