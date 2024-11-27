#include <iostream>
#include <string>

using namespace std;

// Klasa bazowa
class Pojazd {
public:
    // Konstruktor
    Pojazd() {
        cout << "Konstruktor Pojazd" << endl;
    }

    // Wirtualna metoda do przyspieszania
    virtual void przyspiesz() {
        cout << "Pojazd przyspiesza." << endl;
    }

    // Wirtualna metoda do zatrzymywania
    virtual void zatrzymaj() {
        cout << "Pojazd zatrzymuje się." << endl;
    }

    // Wirtualny destruktor
    virtual ~Pojazd() {
        cout << "Destruktor Pojazd" << endl;
    }
};

// Funkcja główna
int main() {
    // Tworzenie obiektu klasy Pojazd
    Pojazd* pojazd = new Pojazd();

    // Wywołanie metod
    pojazd->przyspiesz();
    pojazd->zatrzymaj();

    // Usuwanie obiektu
    delete pojazd;

    return 0;
}
