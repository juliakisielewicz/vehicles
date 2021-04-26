//
// Created by kisie on 12.12.2020.
//

#ifndef POJAZD_H
#define POJAZD_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Wyjatki.h"

class Pojazd {

protected:
    std::string typ;
    std::string wlasciciel;
    std::string kolor;
    std::string p_marka;
    double przebieg = 0.0;
    int ladownosc;
    double cena;
public:

    explicit Pojazd(int lad, double c, std::string t = "", std::string kol = "");
    explicit Pojazd(double c, std::string t = "", std::string kol = "");
    virtual ~Pojazd() = default;
    std::string & przekazKolor() {return kolor; }
    std::string & przekazWlasiciciela() {return wlasciciel; }
    std::string przekazTyp() const {return typ;}
    int przekazLadownosc() const {return ladownosc;}
    virtual void jedz(double km) = 0;
    virtual void p_wypisz(int indeks) const;
    virtual void tankuj(double litry) = 0;

    friend class Fabryka;

};

#endif //POJAZD_H
