#include "classMapa.h"
#include <iostream>

using namespace std;

// Konstruktor
Mapa::Mapa() {}

// Dodawanie lokalizacji do mapy
void Mapa::dodajLokalizacje(const string& nazwa, double szerokosc, double dlugosc) {
    this->lokalizacje.push_back(make_pair(nazwa, make_pair(szerokosc, dlugosc)));
}

// Dodawanie odległości między lokalizacjami
void Mapa::dodajOdleglosc(const string& lokalizacja1, const string& lokalizacja2, double odleglosc) {
    this->odleglosci[make_pair(lokalizacja1, lokalizacja2)] = odleglosc;
    this->odleglosci[make_pair(lokalizacja2, lokalizacja1)] = odleglosc; // Odległość w drugą stronę
}

// Wyświetlanie wszystkich lokalizacji
void Mapa::displayLokalizacje() const {
    cout << "Lokalizacje na mapie:" << endl;
    for (const auto& lokalizacja : this->lokalizacje) {
        cout << "Nazwa: " << lokalizacja.first 
             << ", Szerokość: " << lokalizacja.second.first 
             << ", Długość: " << lokalizacja.second.second << endl;
    }
}

// Wyświetlanie wszystkich odległości
void Mapa::displayOdleglosci() const {
    cout << "Odległości między lokalizacjami:" << endl;
    for (const auto& odleglosc : this->odleglosci) {
        cout << "Odległość między " << odleglosc.first.first 
             << " a " << odleglosc.first.second 
             << ": " << odleglosc.second << " km" << endl;
    }
}

// Znajdowanie lokalizacji
pair<double, double> Mapa::znajdzLokalizacje(const string& nazwa) const {
    for (const auto& lokalizacja : this->lokalizacje) {
        if (lokalizacja.first == nazwa) {
            return lokalizacja.second; // Zwraca współrzędne
        }
    }
    return make_pair(0.0, 0.0); // W przypadku nieznalezienia, zwraca 0,0
}
