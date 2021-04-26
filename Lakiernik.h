//
// Created by kisie on 18.12.2020.
//

#ifndef LAKIERNIK_H
#define LAKIERNIK_H

#include "Fabryka.h"

class Lakiernik {


public:
    Lakiernik() = default;
    ~Lakiernik() = default;
    Lakiernik(Lakiernik &inny) = delete;
    void operator=(const Lakiernik &) = delete;
    static void zmienKolor(const std::string &nowyKolor, Pojazd* p) {
        p->przekazKolor() = nowyKolor;
    }
};

#endif //LAKIERNIK_H
