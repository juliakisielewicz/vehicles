//
// Created by kisie on 04.01.2021.
//

#ifndef WYJATKI_H
#define WYJATKI_H

struct BladWartosci : public std::exception {
    std::string informacja;

    explicit BladWartosci(std::string info) : informacja(std::move(info)) {}
};

struct BladPustegoVectora : public std::exception {
    std::string informacja;

    explicit BladPustegoVectora(std::string info) : informacja(std::move(info)) {}
};

#endif //WYJATKI_H
