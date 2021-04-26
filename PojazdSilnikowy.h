//
// Created by kisie on 12.12.2020.
//

#ifndef POJAZDSILNIKOWY_H
#define POJAZDSILNIKOWY_H

#include "Pojazd.h"

class PojazdSilnikowy : public Pojazd {

protected:
    double ilosc_paliwa = 0.0; //pelny bak: motocykl - 20; samochod - 40
    double spalanie;

public:
    PojazdSilnikowy(double spal, int lad, double c, std::string t = "", std::string kol = "", double paliwo = 0.0);
    void jedz(double km) override;

    friend class Komis;
};

#endif //POJAZDSILNIKOWY_H
