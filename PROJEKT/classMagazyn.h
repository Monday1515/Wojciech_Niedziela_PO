#ifndef CLASSMAGAZYN_H
#define CLASSMAGAZYN_H

#include <string>
#include <vector>
#include "classPaczka.h"  // Zakładamy, że będziemy korzystać z klasy Paczka

using namespace std;

class Magazyn {
private:
    string adres_magazynu;
    vector<Paczka> paczki;

public:
    // Konstruktor
    Magazyn(const string& adres); //: adres_magazynu(adres) {}

    string getAdresMagazynu() const;

    // Dodawanie paczki do magazynu
    void dodajPaczke(const Paczka& paczka);

    // Usuwanie paczki z magazynu
    void usunPaczke(int id_paczki);

    // Pobranie wszystkich paczek
    vector<Paczka> getPaczki() const;

    // Wyświetlanie szczegółów magazynu i paczek
    void displayMagazyn() const;
};

#endif // CLASSMAGAZYN_H
