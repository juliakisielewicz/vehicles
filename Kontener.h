//
// Created by kisie on 03.01.2021.
//

#ifndef KONTENER_H
#define KONTENER_H

template<typename T, int ROZMIAR>
class Kontener{
    T _fab[ROZMIAR] {};

public:
    T& operator[](int indeks)
    {
        if (indeks >= ROZMIAR || indeks < 0)
            throw std::out_of_range("Indeks spoza zakresu");

        return _fab[indeks];
    }

    friend std::ostream &operator<<(std::ostream &s, const Kontener &k) {

        s << "CENNIK WSZYSTKICH FABRYK\n\n";
        for (int i = 0; i < ROZMIAR; i++) {
            s << k._fab[i] << "\n";
        }
        return s;
    }

};

#endif //KONTENER_H
