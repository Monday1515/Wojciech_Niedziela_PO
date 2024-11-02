#include "classTrasa.h"
#include <iostream>

using namespace std;

// Konstruktor
Trasa::Trasa(Kurier* kurier, Magazyn* magazyn, const vector<Paczka>& paczki, Mapa* mapa) {
    this->kurier = kurier;
    this->magazyn = magazyn;
    this->paczki = paczki; // Użyj kopii paczek
    this->mapa = mapa; // Przypisanie wskaźnika na mapę
}

// Dodawanie paczki do trasy
void Trasa::dodajPaczke(const Paczka& paczka) {
    this->paczki.push_back(paczka);
}

// Wyświetlanie szczegółów trasy
void Trasa::displayTrasa() const {
    cout << "Trasa kuriera: " << this->kurier->getNazwa() << endl;
    cout << "Adres magazynu: " << this->magazyn->getAdresMagazynu() << endl;
    cout << "Paczki do dostarczenia:" << endl;

    for (const auto& paczka : this->paczki) {
        paczka.display(); // Zakładając, że paczka ma metodę display()
    }
}

// Metoda do obliczania optymalnej trasy
void Trasa::obliczOptymalnaTrase() const {
    // Szkic metody - można ją rozwinąć o konkretne algorytmy
    cout << "Obliczanie optymalnej trasy..." << endl;
    // Tutaj można zaimplementować algorytmy, takie jak Dijkstra, A*, itp.
}
