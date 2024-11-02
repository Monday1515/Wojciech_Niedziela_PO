#include "classPaczka.h"
#include <iostream>

using namespace std;

// Konstruktor
Paczka::Paczka(int id, const string& adres, double waga) {
    this->id_paczki = id;
    this->adres_dostawy = adres;
    this->waga = waga;
}

// Getter dla ID paczki
int Paczka::getId() const {
    return this->id_paczki;
}

// Getter dla adresu dostawy paczki
string Paczka::getAdres() const {
    return this->adres_dostawy;
}

// Getter dla wagi paczki
double Paczka::getWaga() const {
    return this->waga;
}

// Wyświetlanie informacji o paczce
void Paczka::display() const {
    cout << "Paczka " << this->id_paczki << " do " << this->adres_dostawy
         << " (waga: " << this->waga << " kg)" << endl;
}
