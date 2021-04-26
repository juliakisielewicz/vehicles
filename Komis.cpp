//
// Created by kisie on 19.12.2020.
//

#include "Komis.h"
#include "ObslugaWejscia.h"
#include <cmath>

Komis::~Komis() {
    for (auto p : plac)
        delete p;
    plac.clear();
}

void Komis:: wypisz_doOdkupienia(std::vector<Pojazd*> &lista) {
    std::cout << "Oto pojazdy, ktore komis moze odkupic:" << std::endl;
    std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12) << "kolor"
              << std::setw(10)
              << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
              << "ilosc paliwa" << std::setw(14) << "liczba drzwi" << std::setw(6) << "--" << std::setw(9) << "cena"
              << std::setw(14)
              << "wlasciciel" << std::endl;
    std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10)
              << "[l]" << std::setw(34) << "[pln]" << std::endl;
    std::cout << std::string(115, '-') << std::endl;

    for (int k = 0; k < lista.size(); k++) {
        if (lista[k]->przekazTyp() == "Rower") {
            std::cout << std::setw(2) << k << ".  " << "--" << std::setw(8) << "--" << std::setw(12) << "--"
                      << std::setw(7) << "--" << std::setw(11) << "--" << std::setw(11) << "--" << std::setw(11) << "--" << std::setw(14)
                      << "--" << std::setw(11) << "--" << std::setw(9) << "--" << std::setw(14) << "--" << std::endl;
        }
        else
            lista[k]->p_wypisz(k);
    }
}

void Komis::wypisz_doSprzedania() const {
    if (plac.empty())
        throw BladPustegoVectora("Brak pojazdow w komisie. Powrot do MENU");

    else {
        std::cout << "Oto pojazdy, ktore komis moze sprzedac:" << std::endl;
        std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12) << "kolor"
                  << std::setw(10)
                  << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
                  << "ilosc paliwa" << std::setw(14) << "liczba drzwi"  << std::setw(6) << "--" << std::setw(9) << "cena" << std::setw(14)
                  << "wlasciciel" << std::endl;
        std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10) << "[l]"  << std::setw(34) << "[pln]" << std::endl;
        std::cout << std::string(115, '-') << std::endl;

        for(int k = 0; k < plac.size(); k++)
                plac[k]->p_wypisz(k);
    }
}

template<typename T>
int Komis::wybierz(std::vector<T*> &lista) {
    int indeks;

    std::cout << "Wybierz numer pojazdu: " << std::endl;
    if(ObslugaWejscia::przekazInstancje()->zPliku)
        indeks = stoi(ObslugaWejscia::przekaz());
    else {
        std::string line;
        std::getline(std::cin, line);
        indeks = stoi(line);
    }
    if(indeks < 0 || indeks >= lista.size())
        throw BladWartosci("Blad! Numer spoza zakresu");

    if (lista[indeks]->przekazTyp() == "Rower")
        throw BladWartosci("Pojazd niedostepny");

    return indeks;
}

void Komis::cenaZakupu() {
    double wsp_m;
    if(plac.back()->p_marka == "Opel")
        wsp_m = 0.85;
    else if(plac.back()->p_marka == "Ford")
        wsp_m = 0.8;
    else if(plac.back()->p_marka == "Fiat")
        wsp_m = 0.75;
    else if(plac.back()->p_marka == "Jeep")
        wsp_m = 0.9;
    else {
        std::cout << "Blad" << std::endl;
        return;
    }

    double wsp_p;
    if(plac.back()->przebieg > 300000) {
        wsp_p = 1000;
        plac.back()->cena = wsp_m*wsp_p;
    }
    else {
        wsp_p = exp(plac.back()->przebieg*(-0.00001));
        plac.back()->cena = round(plac.back()->cena*wsp_m*wsp_p);
    }
}

void Komis::odkup(std::vector<Pojazd*> &lista) {
    bool rw = true; //sprawdza czy jest na liście jakiś pojazd nie będący rowerem
    for(int i = 0; i < lista.size(); i++) {
        if(lista[i]->przekazTyp() != "Rower") {
            rw = false;
            i = lista.size();
        }
    }
    if(rw)
        throw BladPustegoVectora("Brak pojazdow, ktore komis moglby odkupic. Powrot do MENU.");

    wypisz_doOdkupienia(lista);

    int indeks;
    bool a = true;
    do {
        try {
            indeks = wybierz<Pojazd>(lista);
            a = false;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Blad! Podana wartosc nie jest liczba" << std::endl;
        }
        catch (std::out_of_range &e) {
            std::cout << "Blad! Podana wartosc nie moze zostac odczytana" << std::endl;
        }
        catch (BladWartosci &e) {
            std::cout << e.informacja << std::endl;
        }
    } while (a);


    lista[indeks]->przekazWlasiciciela() = "komis";
    auto tmp = dynamic_cast<PojazdSilnikowy*>(lista[indeks]);
    lista.erase(lista.begin() + indeks);
    plac.emplace_back(tmp);

    cenaZakupu();
    if(plac.back()->p_marka == "Ford" || plac.back()->p_marka == "Fiat")
        plac.back()->przebieg /= 2;
}

void Komis::sprzedaj(std::vector<Pojazd *> &lista, std::string &kupujacy) {
    try {
        wypisz_doSprzedania();
    }
    catch (BladPustegoVectora &e) {
        std::cout << e.informacja << std::endl;
    }

    int indeks;
    bool a = true;
    do {
        try {
            indeks = wybierz<PojazdSilnikowy>(this->plac);
            a = false;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Blad! Podana wartosc nie jest liczba" << std::endl;
        }
        catch (std::out_of_range &e) {
            std::cout << "Blad! Podana wartosc nie moze zostac odczytana" << std::endl;
        }
        catch (BladWartosci &e) {
            std::cout << e.informacja << std::endl;
        }
    } while (a);

    plac[indeks]->wlasciciel = kupujacy;
    plac[indeks]->cena *= 1.1;
    auto tmp = dynamic_cast<Pojazd*>(plac[indeks]);
    plac.erase(plac.begin() + indeks);
    lista.emplace_back(tmp);

    std::cout << "Sprzedano pojazd. Nowy wlasciciel: " << kupujacy << std::endl;
}

