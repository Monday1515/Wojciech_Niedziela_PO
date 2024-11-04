#include <iostream>
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classTrasa.h"
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Trasa kuriera");


    // Inicjalizacja magazynu
    Magazyn magazyn("Warszawa, ul. Przykladowa 1", 0.0, 0.0);

    // Inicjalizacja kuriera
    Kurier kurier(1, "Jan", "Kowalski", "samochód dostawczy", &magazyn); // Dodano nazwisko

    // Inicjalizacja paczek
    Paczka paczka1(1, "Warszawa, ul. Wspolna 5", 2.5, 30.0, 4.0);
    Paczka paczka2(2, "Warszawa, ul. Krotka 12", 1.0, 6.0, 8.0);
    Paczka paczka3(2, "Warszawa, ul. test 0", 10.0, 10.0, 10.0);

    // Inicjalizacja mapy
    Mapa mapa;
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Wspolna 5", 3.2);
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Krotka 12", 4.5);
    mapa.dodajOdleglosc("Warszawa, ul. Wspolna 5", "Warszawa, ul. Krotka 12", 2.0);
    mapa.dodajOdleglosc("Warszawa, ul. Wspolna 5", "Warszawa, ul. test 0", 2.0);
    mapa.dodajOdleglosc("Warszawa, ul. Krotka 12", "Warszawa, ul. test 0", 2.0);

    // Inicjalizacja trasy
    vector<Paczka> paczki = { paczka1, paczka2, paczka3 };
    Trasa trasa(&kurier, &magazyn, paczki, &mapa);

    // Wyświetlenie trasy
    trasa.displayTrasa();

    cout << endl;

    // Wyznaczenie i wyświetlenie optymalnej trasy metodą algorytmu zachłannego
    vector<Paczka> optymalnaTrasa = trasa.znajdzTraseAlgorytmZachlanny();
    cout << "Optymalna trasa kuriera (algorytm zachlanny):" << endl;
    for (const auto& paczka : optymalnaTrasa) {
        cout << "Dostawa pod adres: " << paczka.getAdres() << endl;
    }

    cout << endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Czyszczenie ekranu
        window.clear();

        // Rysowanie trasy
        trasa.draw(window);

        // Wyświetlenie okna
        window.display();
    }

    return 0;
}
