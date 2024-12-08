#include <iostream>   // rozwiazanie poprawne
#include <string>
#include <vector>
#include <memory>

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
        cout << "Pojazd zatrzymuje sie." << endl;
    }

    // Wirtualny destruktor
    virtual ~Pojazd() {
        cout << "Destruktor Pojazd" << endl;
    }
};

class Samochod : public Pojazd {
public:
    void przyspiesz() override {
        std::cout << "Samochod przyspiesza z uzyciem silnika." << std::endl;
    }

    void zatrzymaj() override {
        std::cout << "Samochod hamuje i zatrzymuje sie." << std::endl;
    } // szkoda, że nie zdefiniował Pan destruktorów w klasach pochodnych
};

// Klasa pochodna: Rower
class Rower : public Pojazd {
public:
    void przyspiesz() override {
        std::cout << "Rowerzysta pedaluje, aby przyspieszyc." << std::endl;
    }

    void zatrzymaj() override {
        std::cout << "Rowerzysta hamuje recznie, aby się zatrzymac." << std::endl;
    }
};

// Klasa pochodna: Motocykl
class Motocykl : public Pojazd {
public:
    void przyspiesz() override {
        std::cout << "Motocykl przyspiesza" << std::endl;
    }

    void zatrzymaj() override {
        std::cout << "Motocykl hamuje" << std::endl;
    }
};

// Klasa pochodna: Skuter
class Skuter : public Pojazd {
public:
    void przyspiesz() override {
        std::cout << "Skuter przyspiesza cicho i spokojnie." << std::endl;
    }

    void zatrzymaj() override {
        std::cout << "Skuter delikatnie hamuje." << std::endl;
    }
};

// Funkcja główna
int main() {

//     // Tworzenie obiektów na wskaźnikach
//     Pojazd* pojazd1 = new Samochod();
//     Pojazd* pojazd2 = new Rower();
//     Pojazd* pojazd3 = new Motocykl();

//     // Testowanie każdego pojazdu
//     std::cout << "Test samochodu:" << std::endl;
//     pojazd1->przyspiesz();
//     pojazd1->zatrzymaj();

//     std::cout << "\nTest roweru:" << std::endl;
//     pojazd2->przyspiesz();
//     pojazd2->zatrzymaj();

//     std::cout << "\nTest motocykla:" << std::endl;
//     pojazd3->przyspiesz();
//     pojazd3->zatrzymaj();

//     // Usuwanie obiektów
//     delete pojazd1;
//     delete pojazd2;
//     delete pojazd3;

//     return 0;
// }

// Wektor wskaźników unique_ptr do obiektów klasy bazowej Pojazd
    std::vector<std::unique_ptr<Pojazd>> pojazdy;

    // Dodawanie różnych pojazdów do wektora
    pojazdy.push_back(std::make_unique<Samochod>());
    pojazdy.push_back(std::make_unique<Rower>());
    pojazdy.push_back(std::make_unique<Motocykl>());
    pojazdy.push_back(std::make_unique<Skuter>()); // Dodanie skutera


    // Wywoływanie metod w sposób polimorficzny
    for (const auto& pojazd : pojazdy) {
        pojazd->przyspiesz();
        pojazd->zatrzymaj();
        std::cout << std::endl;
    }

    // Obiekty są automatycznie zwalniane, ponieważ używamy std::unique_ptr
    return 0;
}
