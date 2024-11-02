#include "classMagazyn.h"
#include <iostream>

// Użycie przestrzeni nazw
using namespace std;

// Konstruktor
Magazyn::Magazyn(const string& adres) {
    this->adres_magazynu = adres;
}

// Dodawanie paczki do magazynu
void Magazyn::dodajPaczke(const Paczka& paczka) {
    this->paczki.push_back(paczka);
}

// Usuwanie paczki z magazynu
void Magazyn::usunPaczke(int id_paczki) {
    for (auto it = this->paczki.begin(); it != this->paczki.end(); ++it) {
        if (it->getId() == id_paczki) {
            this->paczki.erase(it);
            break;
        }
    }
}

// Pobranie wszystkich paczek z magazynu
vector<Paczka> Magazyn::getPaczki() const {
    return this->paczki;
}

// Metoda do pobierania adresu magazynu
string Magazyn::getAdresMagazynu() const {
    return this->adres_magazynu; // Zwraca adres magazynu
}

// Wyświetlanie szczegółów magazynu i przechowywanych paczek
void Magazyn::displayMagazyn() const {
    cout << "Magazyn pod adresem: " << this->adres_magazynu << endl;
    cout << "Przechowywane paczki:" << endl;
    for (const auto& paczka : this->paczki) {
        paczka.display();
    }
}
