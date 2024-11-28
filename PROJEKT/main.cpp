// g++ -o program main.cpp "GRAPHIC INTERFACE/classDraw.cpp" "GRAPHIC INTERFACE/classHandlingEvents.cpp" "GRAPHIC INTERFACE/classDrawMap.cpp" "MECHANICS/classPaczka.cpp" "MECHANICS/classMagazyn.cpp" "MECHANICS/classKurier.cpp" "MECHANICS/classMapa.cpp" "MECHANICS/classTrasa.cpp" -lsfml-graphics -lsfml-window -lsfml-system


// ./program

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/MECHANICS/classPaczka.h"
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/MECHANICS/classMagazyn.h"
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/MECHANICS/classKurier.h"
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/MECHANICS/classMapa.h"
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/MECHANICS/classTrasa.h"
#include <cmath>
#include "C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/GRAPHIC INTERFACE/classDraw.h"


int main()
{
    sf::Font font;
    if (!font.loadFromFile("C:/Users/Admin/Documents/Studia/3 semestr/Programowanie Obiektowe/github/Wojciech_Niedziela_PO/PROJEKT/FONTS/arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    std::vector<std::string> magazynInputBuffers(2, "");
    int magazynStep = 0;
    double magazynX = 0.0, magazynY = 0.0;
    
    classDraw classDraw;

    // Wywołanie metody MagazynInput
    classDraw.MagazynInput(font, magazynInputBuffers, magazynStep, magazynX, magazynY);


    // Jeśli okno zostało zamknięte, kontynuuj do głównego programu
    sf::RenderWindow window(sf::VideoMode(800, 800), "Trasa kuriera");

    // Inicjalizacja magazynu z wprowadzonymi współrzędnymi
    Magazyn magazyn("Warszawa, ul. Przykladowa 1", magazynX, magazynY);

    // Inicjalizacja kuriera
    Kurier kurier(1, "Jan", "Kowalski", "samochód dostawczy", &magazyn);

    // Kontener na paczki
    std::vector<Paczka> paczki;

    // Inicjalizacja mapy
    Mapa mapa;
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Wspolna 5", 3.2);
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Krotka 12", 4.5);
    mapa.dodajOdleglosc("Warszawa, ul. Wspolna 5", "Warszawa, ul. Krotka 12", 2.0);


    classDraw.MainWindow(window, font, paczki, magazyn, kurier, mapa);


    return 0;
}
