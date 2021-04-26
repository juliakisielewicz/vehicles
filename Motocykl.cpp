//
// Created by kisie on 12.12.2020.
//

#include "Motocykl.h"

Motocykl::Motocykl(double spal, int lad, double c, std::string kol): PojazdSilnikowy(spal, lad, c, "Motocykl", std::move(kol), 20.0) {}

void Motocykl::tankuj(double litry) {
    ilosc_paliwa += litry;

    if(ilosc_paliwa > 20.0) {
        std::cout << "Wybrana ilosc przekracza pojemnosc baku, zatankowano do limitu pojemnosci." << std::endl;
        ilosc_paliwa = 20.0;
    }
}

void Motocykl::p_wypisz(int indeks) const {
    std::cout << std::setw(2) << indeks << ". " << p_marka << std::setw(10) << typ << std::setw(9)  << kolor << std::setw(7)
              << przebieg << std::setw(11) << ladownosc << std::setw(11) << spalanie << std::setw(11)
            << std::setprecision(4) << ilosc_paliwa << std::setw(14) << "--" << std::setw(11) << "--" << std::setw(9) << std::setprecision(5) << cena << std::setw(14) << wlasciciel << std::endl;
}