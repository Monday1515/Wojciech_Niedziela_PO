#ifndef CLASSMAPA_H
#define CLASSMAPA_H

#include <vector>
#include <string>
#include <utility>  // Do std::pair
#include <map>      // Do std::map

using namespace std;

class Mapa {
private:
    vector<pair<string, pair<double, double>>> lokalizacje; // Nazwa lokalizacji oraz współrzędne (szerokość, długość)
    map<pair<string, string>, double> odleglosci;           // Mapa odległości między lokalizacjami

public:
    // Konstruktor
    Mapa();

    // Dodawanie lokalizacji
    void dodajLokalizacje(const string& nazwa, double szerokosc, double dlugosc);

    // Dodawanie odległości
    void dodajOdleglosc(const string& lokalizacja1, const string& lokalizacja2, double odleglosc);

    // Wyświetlanie wszystkich lokalizacji
    void displayLokalizacje() const;

    // Wyświetlanie wszystkich odległości
    void displayOdleglosci() const;

    // Metoda do znajdowania lokalizacji (szkic)
    pair<double, double> znajdzLokalizacje(const string& nazwa) const;
};

#endif // CLASSMAPA_H
