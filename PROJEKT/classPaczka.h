#ifndef CLASSPACZKA_H
#define CLASSPACZKA_H

#include <string>
using namespace std;

class Paczka {
private:
    int id_paczki;
    string adres_dostawy;
    double waga;

public:
    // Konstruktor
    Paczka(int id, const string& adres, double waga);

    // Gettery
    int getId() const;
    string getAdres() const;
    double getWaga() const;

    // Metoda do wyświetlania informacji o paczce
    void display() const;
};

#endif // CLASSPACZKA_H
