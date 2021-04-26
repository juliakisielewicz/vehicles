//
// Created by kisie on 21.12.2020.
//

#include "ObslugaWejscia.h"

ObslugaWejscia* ObslugaWejscia::_instancja = nullptr;

ObslugaWejscia *ObslugaWejscia::przekazInstancje() {
    if (_instancja == nullptr) {
        _instancja = new ObslugaWejscia;
    }
    return _instancja;
}

void ObslugaWejscia::wczytaj(const std::string &s) {

    std::string line;
    std::ifstream plik;
    plik.open(s);
    ObslugaWejscia::przekazInstancje()->zPliku = true;

    if (plik.is_open()) {
        while (getline(plik, line)) {
            ObslugaWejscia::przekazInstancje()->instrukcje.push(line);
        }
        plik.close();
    }
}

std::string ObslugaWejscia::przekaz() {
    std::string s = ObslugaWejscia::przekazInstancje()->instrukcje.front();
    ObslugaWejscia::przekazInstancje()->instrukcje.pop();
    return s;
}