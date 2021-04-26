//
// Created by kisie on 12.12.2020.
//

#ifndef FABRYKA_H
#define FABRYKA_H

#include <vector>
#include "Motocykl.h"
#include "Samochod.h"
#include "Rower.h"

class Fabryka {

    std::string f_marka;
    std::vector <Pojazd*> pojazdy;

public:

    explicit Fabryka(std::string fm);
    ~Fabryka();

    //metody
    int ilePojazdow() const { return pojazdy.size(); }
    Pojazd* przekazPojazd(int indeks) const { return pojazdy[indeks]; }
    std::string przekazMarke() const {return f_marka; }
    int wybierz() const;    //pozwala na wybor indeksu tylko dostepnego pojazdu
    bool jestPusty() const { return pojazdy.empty(); };
    void f_wypisz() const;  //wywoluje funkcje "p_wypisz" z danej klasy dziedziczacej po klasie Pojazd
    void konstruuj(Pojazd* p);  //dodaje nowy wskaznik typu Pojazd na koncu vectora "pojazdy"
    Pojazd* sprzedaj(std::string &kupujacy);
    void przejazdzka();   //zwieksza przebieg wybranego samochodu oraz zmniejsza ilosc paliwa (jesli pojazd nie jest rowerem), wywolujac funkcje "jedz" z danej klasy dziedziczacej po klasie Pojazd
};

#endif //FABRYKA_H
