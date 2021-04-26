//
// Created by kisie on 12.12.2020.
//

#include "PojazdSilnikowy.h"

PojazdSilnikowy::PojazdSilnikowy(double spal, int lad, double c, std::string t, std::string kol, double paliwo): Pojazd(lad, c, std::move(t), std::move(kol)), spalanie(spal), ilosc_paliwa(paliwo) {}

void PojazdSilnikowy::jedz(double km) {
    if(ilosc_paliwa - spalanie*km/100 < 0)
        throw BladWartosci("Zbyt malo paliwa, aby pokonac te trase.");

    przebieg = przebieg + km;
    ilosc_paliwa -= spalanie*km/100;
}
