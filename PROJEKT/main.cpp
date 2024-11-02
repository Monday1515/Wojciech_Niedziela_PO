#include <iostream>
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classTrasa.h"

int main() {
    // Inicjalizacja magazynu
    Magazyn magazyn("Warszawa, ul. Przykładowa 1");

    // Inicjalizacja kuriera
    Kurier kurier(1, "Jan", "Kowalski", "samochód dostawczy", &magazyn); // Dodano nazwisko

    // Inicjalizacja paczek
    Paczka paczka1(1, "Warszawa, ul. Wspólna 5", 2.5);
    Paczka paczka2(2, "Warszawa, ul. Krótka 12", 1.0);

    // Inicjalizacja mapy
    Mapa mapa;
    mapa.dodajOdleglosc("Warszawa, ul. Przykładowa 1", "Warszawa, ul. Wspólna 5", 3.2);
    mapa.dodajOdleglosc("Warszawa, ul. Przykładowa 1", "Warszawa, ul. Krótka 12", 4.5);
    mapa.dodajOdleglosc("Warszawa, ul. Wspólna 5", "Warszawa, ul. Krótka 12", 2.0);

    // Inicjalizacja trasy
    vector<Paczka> paczki = { paczka1, paczka2 };
    Trasa trasa(&kurier, &magazyn, paczki, &mapa);

    // Wyświetlenie trasy
    trasa.displayTrasa();

    return 0;
}
