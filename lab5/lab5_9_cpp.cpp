#include <iostream>
using namespace std;

// Klasa bazowa: Pojazd
class Pojazd {
public:
    void uruchom() {
        cout << "Pojazd: Uruchamianie pojazdu." << endl;
    }
    virtual void przyspiesz() {
        cout << "Pojazd: Przyspieszanie ogólne." << endl;
    }
};

// Klasa pochodna: Samochod
class Samochod : public Pojazd {
public:
    void otworzDrzwi() {
        cout << "Samochod: Otwieranie drzwi." << endl;
    }
    void przyspiesz() override {
        cout << "Samochod: Przyspieszanie za pomocą silnika spalinowego." << endl;
    }
};

// Klasa pochodna: ElektrycznySamochod
class ElektrycznySamochod : public Samochod {
public:
    void ladowanie() {
        cout << "ElektrycznySamochod: Ładowanie baterii elektrycznej." << endl;
    }
    void przyspiesz() override {
        cout << "ElektrycznySamochod: Przyspieszanie za pomocą silnika elektrycznego." << endl;
    }
};

int main() {
    // Obiekt klasy ElektrycznySamochod
    ElektrycznySamochod tesla;

    // Metody z różnych poziomów dziedziczenia
    tesla.uruchom();          // Metoda z klasy Pojazd
    tesla.otworzDrzwi();      // Metoda z klasy Samochod
    tesla.ladowanie();        // Metoda z klasy ElektrycznySamochod
    tesla.przyspiesz();       // Nadpisana metoda w ElektrycznySamochod

    return 0;
}
