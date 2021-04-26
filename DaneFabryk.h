//
// Created by kisie on 18.12.2020.
//

#ifndef DANEFABRYK_H
#define DANEFABRYK_H

#include <string>
#include <iostream>

struct DaneFabryk {

    std::string MARKA;

    int S_BAGAZNIK = 0;
    int M_BAGAZNIK = 0;

    double S_SPALANIE = 0.0;
    double M_SPALANIE = 0.0;

    double S_CENA = 0.0;
    double M_CENA = 0.0;
    double R_CENA = 0.0;

    bool juzJest = false;

    DaneFabryk() = default;
    DaneFabryk(std::string marka, int s_bag, int m_bag, double s_spal, double m_spal, double s_c, double m_c, double r_c):
    MARKA(std::move(marka)), S_BAGAZNIK(s_bag), M_BAGAZNIK(m_bag), S_SPALANIE(s_spal), M_SPALANIE(m_spal), S_CENA(s_c), M_CENA(m_c), R_CENA(r_c) {}

    friend std::ostream &operator<<(std::ostream &s, const DaneFabryk &f) {

        s << "marka:\t" << f.MARKA << "\n";
        s << "cena samochodu:\t" << f.S_CENA << "\n";
        s << "cena motocyklu:\t" << f.M_CENA << "\n";
        s << "cena roweru:\t" << f.R_CENA << "\n";
        return s;
    }
};

#endif //DANEFABRYK_H
