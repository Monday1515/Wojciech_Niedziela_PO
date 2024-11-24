#include <iostream>
using namespace std;

// Klasa bazowa: Pojazd
class Pojazd {
public:
    virtual void przyspiesz() {
        cout << "Pojazd: Ogólne przyspieszanie." << endl;
    }
    virtual ~Pojazd() = default; // Wirtualny destruktor
};

// Klasa pośrednia: Silnikowy
class Silnikowy : virtual public Pojazd {
public:
    void przyspiesz() override {
        cout << "Silnikowy: Przyspieszanie za pomocą silnika spalinowego." << endl;
    }
};

// Klasa pośrednia: Elektryczny
class Elektryczny : virtual public Pojazd {
public:
    void przyspiesz() override {
        cout << "Elektryczny: Przyspieszanie za pomocą silnika elektrycznego." << endl;
    }
};

// Klasa pochodna: Hybryda
class Hybryda : public Silnikowy, public Elektryczny {
public:
    void przyspiesz() override {
        cout << "Hybryda: Łączone przyspieszanie z napędu spalinowego i elektrycznego." << endl;
    }
};

int main() {
    Hybryda hybryda;

    hybryda.przyspiesz();

    Pojazd* pojazd = &hybryda;
    pojazd->przyspiesz();

    return 0;
}
