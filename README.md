# vehicles


Utworzono bazową, abstrakcyjną klasę "Pojazd", po której dziedziczą bezpośrednio klasy: "PojazdSilnikowy" (również abstrakcyjna) oraz "Rower". Po klasie "PojazdSilnikowy" dziedziczą z kolei klasy "Samochod" oraz "Motocykl". Dodatkowo utworzono: 

- klasę "Fabryka", która w prywatnym vectorze "pojazdy" przechowuje wskaźniki typu "Pojazd", wskazujące na obiekty poszczególnych pojazdów (Samochod/Motocykl/Rower) - na zasadzie polimorfizmu;
- klasę "Komis", która w prywatnym vectorze "plac" przechowuje wskaźniki typu "PojazdSilnikowy", wskazujące na obiekty poszczególnych pojazdów (Samochod/Motocykl) - na zasadzie polimorfizmu;
- klasę "Lakiernik", która służy do zmieniania koloru wybranego pojazdu;
- strukturę "DaneFabryk", która przechowuje ustalone odgórnie parametry pojazdów tworzonych przez daną fabrykę (ich markę, ładowność, spalanie, cenę) oraz informację o tym czy dana fabryka została już uruchomiona podczas obecnego działania programu;
- szablon klasy "Kontener", wykorzystany do przechowywania w statycznej tablicy czterech opisanych powyżej struktur, utworzonych dla czterech konkretnych fabryk. Dodatkowo klasa "Kontener" umożliwia wyświetlenie cennika;
- klasę "ObslugaWejscia", działającą na zasadzie singletona, która pozwala na wczytywanie komend z pliku tekstowego, którego ścieżka dostępu została podana jako argument uruchomienia programu.
- dwie struktury "BladWartosci" i "BladPustegoVectora", które służą do rzucania wyjątków.

Klasy "Fabryka" i "Komis" zaprzyjaźniono z klasami pojazdów.


Użytkownik ma do dyspozycji MENU GŁÓWNE (w funkcji main) oraz dwa wewnętrzne: MENU FABRYKI (obsługujące pojedynczą fabrykę - w funkcji "wFabryce") oraz MENU KOMISU (obsługujące komis - funkcja "wKomisie"). Dzięki pętli "do while", użytkownik automatycznie wraca do odpowiedniego MENU po zakończeniu danej akcji. Zasada działania każdego MENU oparta jest na instrukcji wielokrotnego wyboru "switch".


- MENU GŁÓWNE pozwala na:
- rozpoczęcie pracy jednej z czterech dostępnych fabryk (czyli przejście do MENU FABRYKI);
- wyświetlenie listy wszystkich pojazdów obecnie dostępnych w fabrykach, z możliwością filtracji pojazdów pod względem ładowności;
- wyświetlenie listy wszystkich obecnie sprzedanych pojazdów (sprzedanych zarówno przez fabrykę, jak i przez komis), czyli pojazdów do których wskaźniki znajdują się w vectorze "sprzedane";
- operacje na sprzedanych obiektach: przemalowanie i tankowanie;
- rozpoczęcie pracy komisu (czyli przejście do MENU KOMISU);
- wyświetlenie cennika, w którym zgromadzono ceny wszystkich rodzajów pojazdów w zależności od marki;
- zakończenie programu.


- MENU FABRYKI:

Przed jego wyświetleniem użytkownik proszony jest o wybór marki jednej z czterech fabryk. Odbywa się to w funkcji "wyborFabryki", która zwraca numer odpowiedniego indeksu vectora "fabryki", przechowującego wskaźniki do Fabryk. Jeśli dana marka wybrana jest po raz pierwszy, tworzony jest nowy obiekt klasy Fabryka, a wskaźnik do niego umieszczany jest na końcu vectora "fabryki" i zwracany jest indeks ostatniego elementu vectora. Jeśli dana marka była już wcześniej wybrana, czyli wskaźnik do wybranej fabryki już znajduje się w vectorze "fabryki", odpowiedni indeks jest wyszukiwany i zwracany. 

Następnie wskaźnik znajdujący się w vectorze "fabryki" na pozycji o danym indeksie jest przekazywany do funkcji "wFabryce", gdzie wyświetlane jest MENU FABRYKI.

MENU FABRYKI pozwala na:
- produkcję nowego pojazdu (użytkownik wybiera rodzaj pojazdu, podaje jego kolor oraz dla samochodu wybiera liczbę drzwi, a dla roweru decyduje czy chce zamontować koszyk);
- sprzedaż wybranego pojazdu;
- przejażdżkę wybranym pojazdem na dowolną odległość (dla samochodów i motocykli ograniczeniem odległości jest posiadana ilość paliwa);
- przemalowanie pojazdu;
- zatankowanie pojazdu;
- wyświetlenie listy pojazdów obecnie dostępnych w fabryce;
- zakończenie pracy fabryki i powrót do MENU GŁÓWNEGO.

MENU KOMISU pozwala na:
- odkupienie jednego z pojazdów, do których wskaźniki znajdują się w vectorze "sprzedane" (dotyczy tylko samochodów i motocykli);
- sprzedaż wybranego pojazdu dostępnego w komisie;
- wyświetlenie listy pojazdów obecnie dostępnych w komisie.


Wyprodukowany w fabryce pojazd dodawany jest poprzez wskaźnik na koniec vectora "pojazdy" (wewnątrz klasy Fabryka), zaś sprzedany przez fabrykę pojazd jest z niego usuwany. Po sprzedaży wskaźnik do pojazdu znajduje się w vectorze "sprzedane" (w main). Z kolei po odkupieniu pojazdu przez komis wskaźnik do pojazdu jest przenoszony do vectora "plac" (wewnątrz klasy Komis). Jeśli pojazd trafia natomiast z komisu do nowego właściciela, wskaźnik do niego ponownie przenoszony jest do vectora "sprzedane". 
"Plac" i "sprzedane" przechowują różnego typu wskaźniki, dlatego przenoszenie wykonywane jest przy użyciu rzutowania "dynamic_cast".

Program posiada instrukcje rzucające i obsługujące wyjątki czterech typów:
- dwóch typów standardowych: "invalid_argument" i "out_of_range", rzucanych przez funkcje "stoi" i "stod";
- dwóch typów utworzonych na potrzeby programu: "BladWartosci" i "BladPustegoVectora". Pierwszy z nich rzucany jest, gdy podana wartość przekracza pewne ustalone wartości brzegowe, drugi natomiast, gdy ma miejsce próba działania na elementach vectora, który nie zawiera żadnych elementów. 
