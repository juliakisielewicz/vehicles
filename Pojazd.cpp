//
// Created by kisie on 12.12.2020.
//

#include "Pojazd.h"

Pojazd::Pojazd(int lad, double c, std::string t, std::string kol): ladownosc(lad), cena(c), typ(std::move(t)), kolor(std::move(kol)) {}
Pojazd::Pojazd(double c, std::string t, std::string kol): ladownosc(0), cena(c), typ(std::move(t)), kolor(std::move(kol)) {}

void Pojazd::p_wypisz(int indeks) const {
  std::cout << std::setw(1) << indeks << ". " << "--" << std::setw(20) << kolor << std::setw(20) << "--" << std::setw(20) << przebieg << std::setw(20) << wlasciciel << std::endl;
}