//
// Created by kisie on 12.12.2020.
//

#include "Rower.h"

Rower::Rower(double c, std::string kol, bool kosz): Pojazd(c, "Rower", std::move(kol)), koszyk(kosz) {
    if(koszyk)
        ladownosc = 10.0;
    else
        ladownosc = 0.0;
}

void Rower::jedz(double km) {
    przebieg = przebieg + km;
}

void Rower::p_wypisz(int indeks) const {
    std::cout << std::setw(2) << indeks << ". " << p_marka << std::setw(10) << typ << std::setw(9)  << kolor << std::setw(7)
                    << przebieg << std::setw(11) << ladownosc << std::setw(11) << "--" << std::setw(11)
                    << "--"  << std::setw(14) << "--" << std::setw(11) << (koszyk ? "tak" : "nie") << std::setw(9) << std::setprecision(5) << cena << std::setw(14) << wlasciciel << std::endl;
}