#include "classTrasa.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <limits>
#include <algorithm>

using namespace std;

// Konstruktor
Trasa::Trasa(Kurier* kurier, Magazyn* magazyn, const vector<Paczka>& paczki, Mapa* mapa) {
    this->kurier = kurier;
    this->magazyn = magazyn;
    this->paczki = paczki; // Użyj kopii paczek
    this->mapa = mapa; // Przypisanie wskaźnika na mapę
}

void Trasa::draw(sf::RenderWindow& window) {
    // Przykład prostego rysowania trasy paczek jako okręgi na ekranie
    sf::CircleShape shape(10); // Punkt reprezentujący paczkę
    shape.setFillColor(sf::Color::Blue);

    for (size_t i = 0; i < paczki.size(); i++) {
        // Ustal przykładową pozycję na ekranie dla każdej paczki
        // W prawdziwym przypadku możesz użyć rzeczywistych współrzędnych
        shape.setPosition(50 + i * 60, 50 + i * 40);  // Przykładowe pozycje
        window.draw(shape);
    }

    // Dodaj linię trasy kuriera
    sf::VertexArray line(sf::LinesStrip, paczki.size());
    for (size_t i = 0; i < paczki.size(); i++) {
        line[i].position = sf::Vector2f(50 + i * 60, 50 + i * 40);
        line[i].color = sf::Color::Red;
    }
    window.draw(line);
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

// // Metoda do obliczania optymalnej trasy
// void Trasa::obliczOptymalnaTrase() const {
//     // Szkic metody - można ją rozwinąć o konkretne algorytmy
//     cout << "Obliczanie optymalnej trasy..." << endl;
//     // Tutaj można zaimplementować algorytmy, takie jak Dijkstra, A*, itp.
// }


// vector<Paczka> Trasa::znajdzTraseAlgorytmZachlanny() {
//     vector<Paczka> optymalnaTrasa;
//     vector<bool> odwiedzone(paczki.size(), false); // Śledzenie odwiedzonych paczek
//     string aktualnaLokacja = magazyn->getAdresMagazynu();

//     while (optymalnaTrasa.size() < paczki.size()) {
//         double minDystans = numeric_limits<double>::max();
//         int najblizszaPaczkaIndex = -1;

//         // Szukaj najbliższej paczki
//         for (size_t i = 0; i < paczki.size(); i++) {
//             if (!odwiedzone[i]) {
//                 double dystans = mapa->odleglosc(aktualnaLokacja, paczki[i].getAdres());
//                 if (dystans < minDystans) {
//                     minDystans = dystans;
//                     najblizszaPaczkaIndex = i;
//                 }
//             }
//         }

//         // Dodaj najbliższą paczkę do trasy i ustaw jej adres jako nową lokalizację
//         if (najblizszaPaczkaIndex != -1) {
//             odwiedzone[najblizszaPaczkaIndex] = true;
//             optymalnaTrasa.push_back(paczki[najblizszaPaczkaIndex]);
//             aktualnaLokacja = paczki[najblizszaPaczkaIndex].getAdres();
//         }
//     }

//     return optymalnaTrasa;
// }


vector<Paczka> Trasa::znajdzTraseAlgorytmZachlanny() {
    vector<Paczka> optymalnaTrasa;
    vector<bool> odwiedzone(paczki.size(), false); 
    double aktualnaX = magazyn->getX();
    double aktualnaY = magazyn->getY();

    while (optymalnaTrasa.size() < paczki.size()) {
        double minDystans = numeric_limits<double>::max();
        int najblizszaPaczkaIndex = -1;

        for (size_t i = 0; i < paczki.size(); i++) {
            if (!odwiedzone[i]) {
                double dystans = mapa->odleglosc(aktualnaX, aktualnaY, paczki[i].getX(), paczki[i].getY());
                if (dystans < minDystans) {
                    minDystans = dystans;
                    najblizszaPaczkaIndex = i;
                }
            }
        }

        if (najblizszaPaczkaIndex != -1) {
            odwiedzone[najblizszaPaczkaIndex] = true;
            optymalnaTrasa.push_back(paczki[najblizszaPaczkaIndex]);
            aktualnaX = paczki[najblizszaPaczkaIndex].getX();
            aktualnaY = paczki[najblizszaPaczkaIndex].getY();
        }
    }

    return optymalnaTrasa;
}


double Trasa::obliczDlugoscTrasy(const vector<Paczka>& trasa) const {
    double dlugosc = 0.0;
    double x = magazyn->getX();
    double y = magazyn->getY();

    for (const auto& paczka : trasa) {
        dlugosc += mapa->odleglosc(x, y, paczka.getX(), paczka.getY());
        x = paczka.getX();
        y = paczka.getY();
    }

    // Dodaj odległość powrotną do magazynu
    dlugosc += mapa->odleglosc(x, y, magazyn->getX(), magazyn->getY());
    return dlugosc;
}

vector<Paczka> Trasa::krzyzowanie(const vector<Paczka>& rodzic1, const vector<Paczka>& rodzic2) {
    int punktPrzeciecia = rand() % rodzic1.size();
    vector<Paczka> dziecko = rodzic1;

    int indeks = punktPrzeciecia;
    for (const auto& paczka : rodzic2) {
        if (find(dziecko.begin(), dziecko.end(), paczka) == dziecko.end()) {
            dziecko[indeks % dziecko.size()] = paczka;
            indeks++;
        }
    }
    return dziecko;
}

void Trasa::mutacja(vector<Paczka>& trasa) {
    int i = rand() % trasa.size();
    int j = rand() % trasa.size();
    swap(trasa[i], trasa[j]);
}

vector<Paczka> Trasa::znajdzTraseAlgorytmGenetyczny(int rozmiarPopulacji, int liczbaPokolen) {
    vector<vector<Paczka>> populacja(rozmiarPopulacji);

    random_device rd;
    mt19937 generator(rd());

    for (int i = 0; i < rozmiarPopulacji; ++i) {
        vector<Paczka> trasa = paczki;
        std::shuffle(trasa.begin(), trasa.end(), generator);
        populacja[i] = trasa;
    }

    for (int pokolenie = 0; pokolenie < liczbaPokolen; ++pokolenie) {
        sort(populacja.begin(), populacja.end(), [this](const vector<Paczka>& a, const vector<Paczka>& b) {
            return obliczDlugoscTrasy(a) < obliczDlugoscTrasy(b);
        });

        vector<vector<Paczka>> nowaPopulacja(populacja.begin(), populacja.begin() + rozmiarPopulacji / 2);

        while (nowaPopulacja.size() < rozmiarPopulacji) {
            int i1 = rand() % (rozmiarPopulacji / 2);
            int i2 = rand() % (rozmiarPopulacji / 2);
            vector<Paczka> dziecko = krzyzowanie(populacja[i1], populacja[i2]);

            if (rand() % 100 < 10) { 
                mutacja(dziecko);
            }

            nowaPopulacja.push_back(dziecko);
        }

        populacja = nowaPopulacja;
    }

    return populacja[0];
}