//
// Created by kisie on 12.12.2020.
//

#ifndef MOTOCYKL_H
#define MOTOCYKL_H

#include "PojazdSilnikowy.h"

class Motocykl : public PojazdSilnikowy {

public:
    Motocykl(double spal, int lad, double c, std::string kol = "");
    void tankuj(double litry) override;
    void p_wypisz(int indeks) const override;

    friend class Fabryka;
    friend class Komis;
};

#endif //MOTOCYKL_H
