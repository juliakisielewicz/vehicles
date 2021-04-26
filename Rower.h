//
// Created by kisie on 12.12.2020.
//

#ifndef ROWER_H
#define ROWER_H


#include "Pojazd.h"

class Rower : public Pojazd {

protected:
    bool koszyk;

public:
    explicit Rower(double c, std::string kol = "", bool kosz = false);
    void jedz(double km) override;

    void p_wypisz(int indeks) const override;
    void tankuj(double litry) final {};

    friend class Fabryka;
    friend class Komis;
};

#endif //ROWER_H
