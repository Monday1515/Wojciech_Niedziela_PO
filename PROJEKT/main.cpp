#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classTrasa.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Trasa kuriera");

    // Inicjalizacja magazynu
    Magazyn magazyn("Warszawa, ul. Przykladowa 1", 0.0, 0.0);

    // Inicjalizacja kuriera
    Kurier kurier(1, "Jan", "Kowalski", "samochód dostawczy", &magazyn);

    // Kontener na paczki
    std::vector<Paczka> paczki;

    // Inicjalizacja mapy
    Mapa mapa;
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Wspolna 5", 3.2);
    mapa.dodajOdleglosc("Warszawa, ul. Przykladowa 1", "Warszawa, ul. Krotka 12", 4.5);
    mapa.dodajOdleglosc("Warszawa, ul. Wspolna 5", "Warszawa, ul. Krotka 12", 2.0);
    mapa.dodajOdleglosc("Warszawa, ul. Wspolna 5", "Warszawa, ul. test 0", 2.0);
    mapa.dodajOdleglosc("Warszawa, ul. Krotka 12", "Warszawa, ul. test 0", 2.0);

    // Tworzenie pól tekstowych dla interfejsu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Upewnij się, że czcionka jest w folderze projektu
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text inputText("Wprowadz dane paczki:", font, 20);
    inputText.setPosition(10, 10);

    sf::Text idText("ID Paczki:", font, 20);
    idText.setPosition(10, 40);
    
    sf::Text adresText("Adres:", font, 20);
    adresText.setPosition(10, 80);
    
    sf::Text wagaText("Waga (kg):", font, 20);
    wagaText.setPosition(10, 120);
    
    sf::Text xText("Wspolrzedna X:", font, 20);
    xText.setPosition(10, 160);
    
    sf::Text yText("Wspolrzedna Y:", font, 20);
    yText.setPosition(10, 200);
    
    sf::RectangleShape inputField(sf::Vector2f(200, 30));
    inputField.setFillColor(sf::Color::White);

    // Tworzenie przycisków "Wyznacz trasę - alg. genetyczny" i "Wyznacz trasę - alg. zachłanny"
    sf::RectangleShape calculateGeneticButton(sf::Vector2f(200, 50));
    calculateGeneticButton.setPosition(10, 250);
    calculateGeneticButton.setFillColor(sf::Color::Green);
    
    sf::Text geneticButtonText("Wyznacz trasę - alg. genetyczny", font, 20);
    geneticButtonText.setPosition(15, 260);
    geneticButtonText.setFillColor(sf::Color::White);
    
    sf::RectangleShape calculateGreedyButton(sf::Vector2f(200, 50));
    calculateGreedyButton.setPosition(220, 250);
    calculateGreedyButton.setFillColor(sf::Color::Blue);
    
    sf::Text greedyButtonText("Wyznacz trasę - alg. zachłanny", font, 20);
    greedyButtonText.setPosition(225, 260);
    greedyButtonText.setFillColor(sf::Color::White);
    
    // To store calculated routes
    std::vector<std::string> routes;

    // To store optimal routes
    std::vector<Paczka> optimalRouteGenetic;
    std::vector<Paczka> optimalRouteGreedy;

    std::string inputBuffer;
    int step = 0;
    int paczkaId;
    std::string adres;
    double waga, x, y;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && step < 20) {
                    inputBuffer += static_cast<char>(event.text.unicode);
                }
                if (event.text.unicode == 8) { // Backspace
                    if (!inputBuffer.empty()) {
                        inputBuffer.pop_back();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                switch (step) {
                    case 0: // ID
                        paczkaId = std::stoi(inputBuffer);
                        break;
                    case 1: // Adres
                        adres = inputBuffer;
                        break;
                    case 2: // Waga
                        waga = std::stod(inputBuffer);
                        break;
                    case 3: // X
                        x = std::stod(inputBuffer);
                        break;
                    case 4: // Y
                        y = std::stod(inputBuffer);
                        // Dodaj paczkę do wektora
                        paczki.emplace_back(paczkaId, adres, waga, x, y);
                        inputBuffer.clear();
                        step = -1; // Resetuje krok
                        break;
                }
                step++;
                inputBuffer.clear(); // Resetuje bufor
                if (step > 4) step = 4; // Ensure step does not exceed the last input
            }

            // Check if the genetic algorithm button is clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (calculateGeneticButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Inicjalizacja trasy
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        
                        // Wyznaczanie tras algorytmem genetycznym
                        optimalRouteGenetic = trasa.znajdzTraseAlgorytmGenetyczny();
                        routes.clear();
                        for (const auto& paczka : optimalRouteGenetic) {
                            routes.push_back("Dostawa pod adres: " + paczka.getAdres());
                        }
                    }
                    
                    // Check if the greedy algorithm button is clicked
                    if (calculateGreedyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Inicjalizacja trasy
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        
                        // Wyznaczanie tras algorytmem zachłannym
                        optimalRouteGreedy = trasa.znajdzTraseAlgorytmZachlanny();
                        routes.clear();
                        for (const auto& paczka : optimalRouteGreedy) {
                            routes.push_back("Dostawa pod adres: " + paczka.getAdres());
                        }
                    }
                }
            }
        }

        window.clear();

        // Rysowanie tekstu
        window.draw(inputText);
        window.draw(idText);
        window.draw(adresText);
        window.draw(wagaText);
        window.draw(xText);
        window.draw(yText);
        
        inputField.setPosition(150, 40 + step * 40); // Ustawia pozycję pola wejściowego
        window.draw(inputField);
        
        // Wyświetlanie wprowadzonego tekstu
        sf::Text currentInput(inputBuffer, font, 20);
        currentInput.setPosition(150, 40 + step * 40);
        window.draw(currentInput);

        // Rysowanie przycisków
        window.draw(calculateGeneticButton);
        window.draw(geneticButtonText);
        window.draw(calculateGreedyButton);
        window.draw(greedyButtonText);

        // Display the entered packages data
        sf::Text packageDataText("Paczki:", font, 20);
        packageDataText.setPosition(10, 320);
        window.draw(packageDataText);

        for (size_t i = 0; i < paczki.size(); ++i) {
            sf::Text packageInfo(std::to_string(paczki[i].getId()) + ": " + paczki[i].getAdres(), font, 20);
            packageInfo.setPosition(10, 350 + i * 30); // Offset each package below the previous
            window.draw(packageInfo);
        }

        // Display the calculated routes
        sf::Text routeTitle("Wyznaczone trasy:", font, 20);
        routeTitle.setPosition(10, 500);
        window.draw(routeTitle);

        for (size_t i = 0; i < routes.size(); ++i) {
            sf::Text routeInfo(routes[i], font, 20);
            routeInfo.setPosition(10, 530 + i * 30); // Offset each route below the previous
            window.draw(routeInfo);
        }

        window.display();
    }

    return 0;
}
