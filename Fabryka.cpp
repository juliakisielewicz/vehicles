//
// Created by kisie on 12.12.2020.
//

#include "Fabryka.h"
#include "ObslugaWejscia.h"

Fabryka::Fabryka(std::string fm) : f_marka(std::move(fm)) {}

Fabryka::~Fabryka() {
    for (auto p : pojazdy)
        delete p;

    pojazdy.clear();
}

int Fabryka::wybierz() const {

    int indeks;
    std::cout << "Wybierz numer pojazdu:" << std::endl;
    if(ObslugaWejscia::przekazInstancje()->zPliku)
        indeks = stoi(ObslugaWejscia::przekaz());
    else {
        std::string line;
        std::getline(std::cin, line);
        indeks = stoi(line);
    }

    if(indeks < 0 || indeks >= pojazdy.size())
        throw BladWartosci("Blad! Numer spoza zakresu");

    return indeks;
}

void Fabryka::f_wypisz() const {
    if(pojazdy.empty())
        throw BladPustegoVectora("Brak dostepnych pojazdow. Powrot do MENU.");

    std::cout << "Oto dostepne pojazdy:" << std::endl;
    std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12)  << "kolor" << std::setw(10)
                        << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
                        << "ilosc paliwa"  << std::setw(14) << "liczba drzwi" << std::setw(8) << "koszyk" << std::setw(7) << "cena" << std::setw(14) << "wlasciciel" << std::endl;
    std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10) << "[l]"  << std::setw(34) << "[pln]" << std::endl;
    std::cout << std::string(115, '-') << std::endl;
    for(int i = 0; i < pojazdy.size(); i++) {
            pojazdy[i]->p_wypisz(i);
    }
}

void Fabryka::konstruuj(Pojazd* p) {
   pojazdy.emplace_back(p);
   pojazdy.back()->wlasciciel = "fabryka";
   pojazdy.back()->p_marka = f_marka;
}


Pojazd* Fabryka::sprzedaj(std::string &kupujacy) {
    int indeks;
    bool a = true;
    do {
        try {
            indeks = wybierz();
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


    pojazdy[indeks]->wlasciciel = kupujacy;
    Pojazd* sprzedany = pojazdy[indeks];
    pojazdy.erase(pojazdy.begin() + indeks);

    std::cout << "Sprzedano pojazd. Nowy wlasciciel: " << kupujacy << std::endl;

    return sprzedany;
}

void Fabryka::przejazdzka() {
    try {
        f_wypisz();
    }
    catch (BladPustegoVectora &e) {
        std::cout << e.informacja << std::endl;
        return;
    }

    int indeks;
    bool a = true;
    do {
        try {
            indeks = wybierz();
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


    double odleglosc;
    bool b = true;
    do {
        std::cout << "Jak daleko chcesz pojechac? [km]: " << std::endl;
        try {
            if (ObslugaWejscia::przekazInstancje()->zPliku)
                odleglosc = stod(ObslugaWejscia::przekaz());
            else {
                std::string line;
                std::getline(std::cin, line);
                odleglosc = stod(line);
            }
            if (odleglosc >= 0)
                b = false;
            else
                std::cout << "Blad! Podana wartosc jest ujemna" << std::endl;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Blad! Podana wartosc nie jest liczba" << std::endl;
        }
        catch (std::out_of_range &e) {
            std::cout << "Blad! Podana wartosc nie moze zostac odczytana" << std::endl;
        }
    } while (b);

    try {
        pojazdy[indeks]->jedz(odleglosc);
    }
    catch (BladWartosci &e) {
        std::cout << e.informacja << std::endl;
    }
}