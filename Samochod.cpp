//
// Created by kisie on 12.12.2020.
//

#include "Samochod.h"

Samochod::Samochod(double spal, int lad, double c, std::string kol, int ld): PojazdSilnikowy(spal, lad, c, "Samochod", std::move(kol), 40.0), liczba_drzwi(ld) {}

void Samochod::tankuj(double litry) {
    ilosc_paliwa += litry;

    if(ilosc_paliwa > 40.0) {
        std::cout << "Wybrana ilosc przekracza pojemnosc baku, zatankowano do limitu pojemnosci." << std::endl;
        ilosc_paliwa = 40.0;
    }
}

void Samochod::p_wypisz(int indeks) const {
    std::cout << std::setw(2) << indeks << ". " << p_marka << std::setw(10) << typ << std::setw(9)  << kolor << std::setw(7)
                << przebieg << std::setw(11) << ladownosc << std::setw(11) << spalanie << std::setw(11)
                << std::setprecision(4) << ilosc_paliwa  << std::setw(14) << liczba_drzwi << std::setw(11) << "--" << std::setw(9)
                << std::setprecision(5) << cena << std::setw(14) << wlasciciel << std::endl;
}