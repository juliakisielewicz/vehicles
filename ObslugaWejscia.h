//
// Created by kisie on 21.12.2020.
//

#ifndef OBSLUGAWEJSCIA_H
#define OBSLUGAWEJSCIA_H

#include <string>
#include <queue>
#include <fstream>

class ObslugaWejscia {
    static ObslugaWejscia *_instancja;
    ObslugaWejscia() = default;
    ~ObslugaWejscia() = default;

public:
    bool zPliku = false;
    std::queue<std::string> instrukcje;

    ObslugaWejscia(ObslugaWejscia &inny) = delete;
    void operator=(const ObslugaWejscia &) = delete;
    static ObslugaWejscia *przekazInstancje();
    static void wczytaj(const std::string &s);
    static std::string przekaz();
};




#endif //OBSLUGAWEJSCIA_H
