//
// Created by kisie on 12.12.2020.
//

#include "Fabryka.h"
#include "DaneFabryk.h"
#include "Komis.h"
#include "Lakiernik.h"
#include "ObslugaWejscia.h"
#include "Kontener.h"

using namespace std;

int wczytajInt();
double wczytajDouble();
string wczytajString();

int wyborFabryki(Kontener<DaneFabryk, 4> &k, vector<Fabryka*> &lista);    //przy pierwszym wejsciu do fabryki tworzony jest jej obiekt, a wskaznik do niego dodawany jest do vectora,
                                                                // zas przy kolejnych wywolaniach wyszukiwana jest odpowiednia, juz istniejaca fabryka
void produkcja(Kontener<DaneFabryk, 4> &k, Fabryka *fabryka);    //tworzy odpowiedni pojazd, wywolujac funkcje "konstruuj" z klasy "Fabryka"
void wFabryce(Kontener<DaneFabryk, 4> &k, Fabryka* fabryka, vector<Pojazd*> &sprzedaz);    //pozwala na dzialania w obrebie wybranej fabryki
void przemaluj_wFabryce(Fabryka* &lista);
void przemalujSprzedane(vector<Pojazd*> &lista);
void zatankuj_wFabryce(Fabryka* &lista);
void zatankujSprzedane(vector<Pojazd*> &lista);
void wypiszDostepne(vector<Fabryka*> &lista);
void wypiszSprzedane( vector<Pojazd*> &lista);
void wKomisie(Komis *kom, vector<Pojazd*> &lista);  //pozwala na dzialania w obrebie komisu
void filtruj(vector<Fabryka*> &lista);  //ukrywa wybrane elementy przy wypisywaniu dostepnych pojazdow
void wypiszSfiltrowane(vector<Fabryka*> &lista, string &typ, int min = 1);


int main(int argc, char* argv[]) {

    if(argc > 1)
        ObslugaWejscia::wczytaj(argv[1]);

    Kontener<DaneFabryk, 4> kontener;
    try {
        kontener[0] = DaneFabryk("Opel", 300, 42, 6.2, 3.9, 52400, 26000, 2100);
    }
    catch (out_of_range &e) {
        cout << e.what() << endl;
        return 0;
    }

    try {
        kontener[1] = DaneFabryk("Ford", 260, 62, 7.7, 4.1, 70300, 29500, 2700);
    }
    catch (out_of_range &e) {
        cout << e.what() << endl;
        return 0;
    }

    try {
        kontener[2] = DaneFabryk("Fiat", 410, 36, 5.8, 3.5, 62200, 22900, 1900);
    }
    catch (out_of_range &e) {
        cout << e.what() << endl;
        return 0;
    }

    try {
        kontener[3] = DaneFabryk("Jeep", 340, 55, 6.3, 4.8, 90700, 31100, 3200);
    }
    catch (out_of_range &e) {
        cout << e.what() << endl;
        return 0;
    }

    int wybor_glowny;
    vector<Fabryka*> fabryki;
    vector<Pojazd*> sprzedane;
    Komis komis;

    do {
        cout << "\n<<<<<<<< MENU GLOWNE >>>>>>>>\n"
                "-> 1. Rozpocznij prace wybranej fabryki\n"
                "-> 2. Zobacz liste pojazdow dostepnych we wszystkich fabrykach\n"
                "-> 3. Zobacz liste wszystkich sprzedanych pojazdow\n"
                "-> 4. Oddaj do lakiernika jeden ze sprzedanych pojazdow\n"
                "-> 5. Zatankuj jeden ze sprzedanych pojazdow\n"
                "-> 6. Rozpocznij prace komisu\n"
                "-> 7. Zobacz cennik wszystkich fabryk\n"
                "-> 0. Zakoncz dzialanie programu\n"
                "Wybierz akcje: " << endl;
        try {
            wybor_glowny = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            wybor_glowny = 10;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            wybor_glowny = 10;
        }


        switch (wybor_glowny) {
            case 0:     //koniec programu
                break;
            case 1:     //wejscie do fabryki

                wFabryce(kontener, fabryki[wyborFabryki(kontener, fabryki)], sprzedane);  //funkcja "wyborFabryki" zwraca wybraną pozycję w vectorze "fabryki",
                                                                                        // na której znajduje się wskaźnik do obiektu klasy Fabryka.
                                                                                        // Wskaznik ten jest przekazywany do funkcji "wFabryce",
                                                                                        // która wykonuje operacje na wskazywanym obiekcie.
                break;
            case 2:
                try {
                    wypiszDostepne(fabryki);
                }
                catch (BladPustegoVectora &e) {
                    cout << e.informacja << endl;
                }
                break;
            case 3:
                try {
                    wypiszSprzedane(sprzedane);
                }
                catch (BladPustegoVectora &e) {
                    cout << e.informacja << endl;
                }
                break;
            case 4:
                przemalujSprzedane(sprzedane);
                break;
            case 5:
                zatankujSprzedane(sprzedane);
                break;
            case 6:     //wejscie do komisu
                wKomisie(&komis, sprzedane);
                break;
            case 7:
                cout << endl << kontener;
                break;
            default:
                cout << "Wybierz numer ponownie" << endl;
                break;
        }
    } while (wybor_glowny != 0);

    //usuwanie wszystkich wskaznikow
    for (auto p : fabryki)
        delete p;
    fabryki.clear();

    for (auto p : sprzedane)
        delete p;
    sprzedane.clear();

}

//*********************************************************************************************************************

int wczytajInt() {

    if(ObslugaWejscia::przekazInstancje()->zPliku) {
        return stoi(ObslugaWejscia::przekaz());
    }
    else {
        string line;
        getline(cin, line);
        return stoi(line);
    }
}

double wczytajDouble() {

    if(ObslugaWejscia::przekazInstancje()->zPliku) {
        return stod(ObslugaWejscia::przekaz());
    }
    else {
        string line;
        getline(cin, line);
        return stod(line);
    }
}

string wczytajString() {
    string line;
    if(ObslugaWejscia::przekazInstancje()->zPliku) {
        return ObslugaWejscia::przekaz();
    }
    else
        getline(cin, line);
    return line;
}

int wyborFabryki(Kontener<DaneFabryk, 4> &k, vector<Fabryka*> &lista) {
    int marka;
    do {
        cout << "Wybierz fabryke: " << endl;    //dostepne sa 4 fabryki
        for(int i = 0; i < 4; i++)
            cout << i << ". " << k[i].MARKA << endl;
        try {
            marka = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            marka = 4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            marka = 4;
        }
    } while (marka < 0 || marka > 3);

    if (k[marka].juzJest) {
        for(int i=0; i<lista.size(); i++) {
            if(lista[i]->przekazMarke() == k[marka].MARKA)
                return i;                                //zwraca indeks juz istniejacego elementu
        }
    }

    k[marka].juzJest = true;
    auto fabryka = new Fabryka(k[marka].MARKA);
    lista.emplace_back(fabryka);
    return static_cast<int>(lista.size())-1;            //zwraca indeks nowego, dodanego na koncu vectora elementu
}

void produkcja(Kontener<DaneFabryk, 4> &k, Fabryka *fabryka) {
    const string typy[3] = {"samochod", "motocykl", "rower"};
    int typ;
    do {
        cout << "Jaki pojazd chcesz wyprodukowac?\n"
                "0. Samochod\n"
                "1. Motocykl\n"
                "2. Rower" << endl;
        try {
            typ = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            typ = 4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            typ = 4;
        }
    } while(typ < 0 || typ > 2);

    string kolor;
    cout << "Jaki kolor ma miec " << typy[typ] << "?:" << endl;
    kolor = wczytajString();
    int marka;
    for(int i = 0; i < 4; i++) {
        if (fabryka->przekazMarke() == k[i].MARKA)
            marka = i;
    }

    switch (typ) {  //produkuje wybrany rodzaj pojazdu
        case 0: {   //Samochod
            int drzwi;
            do {
                cout << "Ile drzwi ma miec " << typy[typ] << "? (do wyboru: 2, 3, 4, 5): " << endl;
                try {
                    drzwi = wczytajInt();
                }
                catch (invalid_argument &e) {
                    cout << "Blad! Podana wartosc nie jest liczba" << endl;
                    drzwi = 6;
                }
                catch (out_of_range &e) {
                    cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                    drzwi = 6;
                }
            } while (drzwi<2 || drzwi>5);

            Pojazd* poj;
            poj = new Samochod(k[marka].S_SPALANIE, k[marka].S_BAGAZNIK, k[marka].S_CENA, kolor, drzwi);
            fabryka->konstruuj(poj);
            break;
        }
        case 1: {   //Motocykl
            Pojazd* poj;
            poj = new Motocykl(k[marka].M_SPALANIE, k[marka].M_BAGAZNIK, k[marka].M_CENA, kolor);
            fabryka->konstruuj(poj);
            break;
        }
        case 2: {   //Rower
            int koszyk;
            do {
                cout << "Czy chcesz zamontowac koszyk?\n"
                        "0. Nie\n"
                        "1. Tak" << endl;
                try {
                    koszyk = wczytajInt();
                }
                catch (invalid_argument &e) {
                    cout << "Blad! Podana wartosc nie jest liczba" << endl;
                    koszyk = 4;
                }
                catch (out_of_range &e) {
                    cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                    koszyk = 4;
                }
            } while(koszyk<0 || koszyk>1);

            Pojazd* poj;
            poj = new Rower(k[marka].R_CENA, kolor, koszyk);
            fabryka->konstruuj(poj);
            break;
        }
        default:
            break;
    }
}

void wFabryce(Kontener<DaneFabryk, 4> &k, Fabryka* fabryka, vector <Pojazd*> &sprzedaz) {
    int wybor;
    do {
        cout << "\n<<<<<<<< MENU FABRYKI >>>>>>>>\n"
                "-> 1. Wyprodukuj nowy pojazd\n"
                "-> 2. Sprzedaj pojazd\n"
                "-> 3. Pojedz wybranym pojazdem\n"
                "-> 4. Oddaj pojazd do lakiernika\n"
                "-> 5. Zatankuj pojazd\n"
                "-> 6. Zobacz wykaz pojazdow w fabryce\n"
                "-> 0. Zakoncz prace fabryki i wroc do MENU GLOWNEGO\n"
                "Wybierz akcje: " << endl;
        try {
            wybor = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            wybor = 10;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            wybor = 10;
        }

        switch (wybor) {
            case 0:     //koniec dzialania funkcji "wFabryce"
                break;
            case 1:
                produkcja(k, fabryka);
                break;
            case 2: {   //sprzedac pojazd mozna tylko jesli w fabryce jest choc jeden dostepny pojazd
                try {
                    fabryka->f_wypisz();
                }
                catch (BladPustegoVectora &e) {
                    std::cout << e.informacja << std::endl;
                    break;
                }
                cout << "Podaj nazwisko kupujacego: " << endl;
                string nazwisko = wczytajString();
                sprzedaz.push_back(fabryka->sprzedaj(nazwisko));    //na koncu vectora dodany zostaje wskaznik do obiektu typu Pojazd zwrocony przez metode "sprzedaj"
                break;
            }
            case 3:
                fabryka->przejazdzka();
                break;
            case 4:
                przemaluj_wFabryce(fabryka);
                break;
            case 5:
                zatankuj_wFabryce(fabryka);
                break;
            case 6:
                try {
                    fabryka->f_wypisz();
                }
                catch (BladPustegoVectora &e) {
                    cout << e.informacja << endl;
                }
                break;
            default:
                cout << "Wybierz numer ponownie" << endl;
                break;
        }
    } while (wybor != 0);

}

void przemaluj_wFabryce(Fabryka* &lista) {  //dziala Lakiernik
    try {
        lista->f_wypisz();
    }
    catch (BladPustegoVectora &e) {
        cout << e.informacja << endl;
        return;
    }

    int poj;
    bool a = true;
    do {
        try {
            poj = lista->wybierz();
            a = false;
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            poj = -4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            poj = -4;
        }
        catch (BladWartosci &e) {
            cout << e.informacja << endl;
        }
    } while (a);

    cout << "Na jaki kolor przemalowac " << lista->przekazPojazd(poj)->przekazTyp() << "?: " << endl;
    string nKolor = wczytajString();
    Lakiernik::zmienKolor(nKolor, lista->przekazPojazd(poj));
}

void przemalujSprzedane(vector<Pojazd*> &lista) {   //dziala Lakiernik
    try {
        wypiszSprzedane(lista);
    }
    catch (BladPustegoVectora &e) {
        cout << e.informacja << endl;
        return;
    }

    int poj;
    do {
        cout << "Wybierz numer pojazdu: " << endl;
        try {
            poj = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            poj = -4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            poj = -4;
        }
    } while (poj < 0 || poj >= lista.size());

    cout << "Na jaki kolor przemalowac " << lista[poj]->przekazTyp() << "?: " << endl;
    string nKolor = wczytajString();
    Lakiernik::zmienKolor(nKolor, lista[poj]);
}

void zatankuj_wFabryce(Fabryka* &lista) {
    try {
        lista->f_wypisz();
    }
    catch (BladPustegoVectora &e) {
        cout << e.informacja << endl;
        return;
    }
    int poj;
    bool rw;    //sprawdza czy nie wybrano roweru
    bool a;
    do {
        rw = false;
        a = true;
        do {
            try {
                poj = lista->wybierz();
                a = false;
            }
            catch (invalid_argument &e) {
                cout << "Blad! Podana wartosc nie jest liczba" << endl;
                poj = -4;
            }
            catch (out_of_range &e) {
                cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                poj = -4;
            }
            catch (BladWartosci &e) {
                cout << e.informacja << endl;
            }
        }while (a);

        if (lista->przekazPojazd(poj)->przekazTyp() == "Rower") {
            cout << "Nie mozna zatankowac roweru" << endl;
            rw = true;
        }
    }  while(rw);

    double ile;
    do {
        cout << "Ile litrow chcesz zatankowac (pojemnosc baku: " << (lista->przekazPojazd(poj)->przekazTyp() == "Samochod" ? "40l" : "20l") << ")?: " << endl;
        try {
            ile = wczytajDouble();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            ile = -4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            ile = -4;
        }
    } while(ile < 0.0);
    lista->przekazPojazd(poj)->tankuj(ile);
}
void zatankujSprzedane(vector<Pojazd*> &lista) {
    try {
        wypiszSprzedane(lista);
    }
    catch (BladPustegoVectora &e) {
        cout << e.informacja << endl;
        return;
    }

    int poj;
    bool rw;    //sprawdza czy nie wybrano roweru
    do {
        rw = false;
        do {
            cout << "Wybierz numer pojazdu: " << endl;
            try {
                poj = wczytajInt();
            }
            catch (invalid_argument &e) {
                cout << "Blad! Podana wartosc nie jest liczba" << endl;
                poj = -4;
            }
            catch (out_of_range &e) {
                cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                poj = -4;
            }
        }while (poj < 0 || poj >= lista.size());

        if (lista[poj]->przekazTyp() == "Rower") {
            cout << "Nie mozna zatankowac roweru" << endl;
            rw = true;
        }
    }  while(rw);

    double ile;
    do {
        cout << endl << "Ile litrow chcesz zatankowac (pojemnosc baku: " << (lista[poj]->przekazTyp() == "Samochod" ? "40l" : "20l") << ")?: " << endl;
        try {
            ile = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            ile = -4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            ile = -4;
        }
    } while(ile < 0.0);
    lista[poj]->tankuj(ile);
}

void  wypiszDostepne(vector <Fabryka*> &lista) {
    bool nieMaPojazdow = true;
    for(auto i : lista) {
        if(!i->jestPusty())
            nieMaPojazdow = false;
    }
    if(nieMaPojazdow)
        throw BladPustegoVectora("Brak dostepnych pojazdow.");

    cout << "Oto wszystkie dostepne pojazdy:" << endl;
    std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12)  << "kolor" << std::setw(10)
              << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
              << "ilosc paliwa"  << std::setw(14) << "liczba drzwi" << std::setw(8) << "koszyk" << std::setw(7) << "cena" << std::setw(14) << "wlasciciel" << std::endl;
    std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10) << "[l]"  << std::setw(34) << "[pln]" << std::endl;
    std::cout << std::string(115, '-') << std::endl;

    int lp = 0;
    for(auto i : lista) {     //wypisuje wszystkie dostepne pojazdy z fabryk zawartych w vectorze "lista"
        for(int k = 0; k < i->ilePojazdow(); k++) {
            i->przekazPojazd(k)->p_wypisz(lp);
            lp++;
        }
    }
    filtruj(lista);
}

void wypiszSprzedane(vector <Pojazd*> &lista) {
    if(lista.empty())
        throw BladPustegoVectora("Brak sprzedanych pojazdow. Pojazd sprzedac mozna podczas pracy fabryki lub komisu.");

    cout << "Oto sprzedane pojazdy:" << endl;
    std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12)  << "kolor" << std::setw(10)
              << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
              << "ilosc paliwa"  << std::setw(14) << "liczba drzwi" << std::setw(8) << "koszyk" << std::setw(7) << "cena" << std::setw(14) << "wlasciciel" << std::endl;
    std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10) << "[l]"  << std::setw(34) << "[pln]" << std::endl;
    std::cout << std::string(115, '-') << std::endl;

    for(int k = 0; k < lista.size(); k++)
        lista[k]->p_wypisz(k);
}

void wKomisie(Komis* kom, vector<Pojazd*> &lista) {
    int wybor;
    do {
        cout << "\n<<<<<<<< MENU KOMISU >>>>>>>>\n"
                "-> 1. Odkup pojazd od klienta\n"
                "-> 2. Sprzedaj pojazd klientowi\n"
                "-> 3. Zobacz wykaz pojazdow dostepnych w komisie\n"
                "-> 0. Zakoncz prace komisu i wroc do MENU GLOWNEGO\n"
                "Wybierz akcje: " << endl;
        try {
            wybor = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            wybor = 10;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            wybor = 10;
        }

        switch (wybor) {
            case 0:     //koniec dzialania funkcji "wKomisie"
                break;
            case 1: {
                try {
                    kom->odkup(lista);
                }
                catch (BladPustegoVectora &e) {
                    cout << e.informacja << endl;
                }
                break;
            }
            case 2: {   //sprzedac pojazd mozna tylko jesli w komisie jest choc jeden dostepny pojazd
                if(kom->jestPusty())
                    cout << "Brak dostepnych pojazdow. Powrot do MENU." << endl;
                else {
                    cout << "Podaj nazwisko kupujacego: " << endl;
                    string nazwisko = wczytajString();
                    kom->sprzedaj(lista, nazwisko);
                }
                break;
            }
            case 3: {
                try {
                    kom->wypisz_doSprzedania();
                }
                catch (BladPustegoVectora &e) {
                    cout << e.informacja << endl;
                }
                break;
            }
            default:
                cout << "Wybierz numer ponownie" << endl;
                break;
        }
    } while (wybor != 0);

}

void filtruj(vector<Fabryka*> &lista) {
    int wyb;
    do {
        cout << endl << "Czy chcesz wlaczyc filtrowanie pojazdow pod wzgledem ladownosci?\n"
                "0. Nie\n"
                "1. Tak" << endl;
        try {
            wyb = wczytajInt();
        }
        catch (invalid_argument &e) {
            cout << "Blad! Podana wartosc nie jest liczba" << endl;
            wyb = 4;
        }
        catch (out_of_range &e) {
            cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
            wyb = 4;
        }
    } while(wyb<0 || wyb>1);

    if(wyb == 0)
        return;
    else {
        do {
            cout << "Dostepne opcje filtracji:" << endl;
            cout << "1. Ukryj rowery bez koszykow\n"
                    "2. Ukryj samochody o ladownosci mniejszej niz podana (najmniejsza wynosi 260 kg)\n"
                    "3. Ukryj motocykle o ladownosci mniejszej niz podana (najmniejsza wynosi 36 kg)\n"
                    "Wybor: " << endl;
            try {
                wyb = wczytajInt();
            }
            catch (invalid_argument &e) {
                cout << "Blad! Podana wartosc nie jest liczba" << endl;
                wyb = 10;
            }
            catch (out_of_range &e) {
                cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                wyb = 10;
            }
        } while(wyb < 1 || wyb > 3);

        int min;
        if(wyb == 2 || wyb == 3) {
            do {
                cout << "Minimalna ladownosc (liczba calkowita): " << endl;
                try {
                    min = wczytajInt();
                }
                catch (invalid_argument &e) {
                    cout << "Blad! Podana wartosc nie jest liczba" << endl;
                    min = -4;
                }
                catch (out_of_range &e) {
                    cout << "Blad! Podana wartosc nie moze zostac odczytana" << endl;
                    min = -4;
                }
            } while(min < 0);
        }

        cout << "Oto dostepne pojazdy po sfiltrowaniu:" << endl;
        std::cout << "Lp. " << std::setw(2) << "marka" << std::setw(6) << "typ" << std::setw(12)  << "kolor" << std::setw(10)
                  << "przebieg" << std::setw(11) << "ladownosc" << std::setw(10) << "spalanie" << std::setw(14)
                  << "ilosc paliwa"  << std::setw(14) << "liczba drzwi" << std::setw(8) << "koszyk" << std::setw(7) << "cena" << std::setw(14) << "wlasciciel" << std::endl;
        std::cout << std::setw(35) << "[km]" << std::setw(10) << "[kg]" << std::setw(13) << "[l/100km]" << std::setw(10) << "[l]"  << std::setw(34) << "[pln]" << std::endl;
        std::cout << std::string(115, '-') << std::endl;

        string filtrowanePojazdy;
        switch (wyb) {
            case 1:
                filtrowanePojazdy = "Rower";
                wypiszSfiltrowane(lista, filtrowanePojazdy);
                break;
            case 2:
                filtrowanePojazdy = "Samochod";
                wypiszSfiltrowane(lista, filtrowanePojazdy, min);
                break;
            case 3:
                filtrowanePojazdy = "Motocykl";
                wypiszSfiltrowane(lista, filtrowanePojazdy, min);
                break;
            default:
                break;
        }

    }
}

void wypiszSfiltrowane(vector<Fabryka*> &lista, string &typ, int min) {
    int lp = 0;
    for(auto i : lista) {
        for(int k = 0; k < i->ilePojazdow(); k++) {
            if(i->przekazPojazd(k)->przekazTyp() != typ || (i->przekazPojazd(k)->przekazTyp() == typ && i->przekazPojazd(k)->przekazLadownosc() >= min)) {
                i->przekazPojazd(k)->p_wypisz(lp);
                lp++;
            }
        }
    }
}