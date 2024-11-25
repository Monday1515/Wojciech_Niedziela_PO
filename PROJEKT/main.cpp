// g++ -o program main.cpp classPaczka.cpp classMagazyn.cpp classKurier.cpp classMapa.cpp classTrasa.cpp -lsfml-graphics -lsfml-window -lsfml-system
// ./program

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

    // Tworzenie pól tekstowych dla interfejsu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Upewnij się, że czcionka jest w folderze projektu
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text inputText("Wprowadz dane paczki:", font, 20);
    inputText.setPosition(100, 10);

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
    
    sf::RectangleShape inputField(sf::Vector2f(1, 30));
    inputField.setFillColor(sf::Color::White);

    // Tworzenie przycisków "Wyznacz trasę - alg. genetyczny" i "Wyznacz trasę - alg. zachłanny"
    sf::RectangleShape calculateGeneticButton(sf::Vector2f(200, 50));
    calculateGeneticButton.setPosition(10, 250);
    calculateGeneticButton.setFillColor(sf::Color::Green);
    
    sf::Text geneticButtonText("alg. genetyczny", font, 20);
    geneticButtonText.setPosition(15, 260);
    geneticButtonText.setFillColor(sf::Color::White);
    
    sf::RectangleShape calculateGreedyButton(sf::Vector2f(200, 50));
    calculateGreedyButton.setPosition(220, 250);
    calculateGreedyButton.setFillColor(sf::Color::Blue);
    
    sf::Text greedyButtonText("alg. zachlanny", font, 20);
    greedyButtonText.setPosition(225, 260);
    greedyButtonText.setFillColor(sf::Color::White);

    // Tworzenie przycisku "MAPA"
    sf::RectangleShape mapButton(sf::Vector2f(200, 50));
    mapButton.setPosition(640, 10);
    mapButton.setFillColor(sf::Color::Magenta);
    
    sf::Text mapButtonText("MAPA", font, 20);
    mapButtonText.setPosition(660, 20);
    mapButtonText.setFillColor(sf::Color::White);

    // Buffers for inputs
    std::vector<std::string> inputBuffers(5, ""); // Buffers for ID, Address, Weight, X, Y
    int step = 0; // Step tracker for the current field
    int paczkaId;
    std::string adres;
    double waga, x, y;

    // Store calculated routes
    std::vector<std::string> routes;

    bool showMap = false; // Flag to indicate if the map window should be shown

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && step < 5) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == 8) { // Backspace
                        if (!inputBuffers[step].empty())
                            inputBuffers[step].pop_back();
                    } else {
                        inputBuffers[step] += enteredChar;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                switch (step) {
                    case 0: // ID
                        paczkaId = std::stoi(inputBuffers[step]);
                        break;
                    case 1: // Address
                        adres = inputBuffers[step];
                        break;
                    case 2: // Weight
                        waga = std::stod(inputBuffers[step]);
                        break;
                    case 3: // X Coordinate
                        x = std::stod(inputBuffers[step]);
                        break;
                    case 4: // Y Coordinate
                        y = std::stod(inputBuffers[step]);
                        paczki.emplace_back(paczkaId, adres, waga, x, y);

                        // Resetowanie buforów i kroku po dodaniu paczki
                        inputBuffers = std::vector<std::string>(5, ""); // Wyczyść bufory
                        step = -1; // Zresetuj krok
                        break;
                }
                step++;
                if (step > 4) step = 4; // Ensure step does not exceed the last input field
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (calculateGeneticButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Wyznaczanie tras algorytmem genetycznym
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        auto optimalRouteGenetic = trasa.znajdzTraseAlgorytmGenetyczny();
                        routes.clear();
                        for (const auto& paczka : optimalRouteGenetic) {
                            routes.push_back("Dostawa pod adres: " + paczka.getAdres());
                        }
                    }
                    
                    if (calculateGreedyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Wyznaczanie tras algorytmem zachłannym
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        auto optimalRouteGreedy = trasa.znajdzTraseAlgorytmZachlanny();
                        routes.clear();
                        for (const auto& paczka : optimalRouteGreedy) {
                            routes.push_back("Dostawa pod adres: " + paczka.getAdres());
                        }
                    }

                    if (mapButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        showMap = true; // Set flag to show map window
                    }
                }
            }
        }

        window.clear();

        // Rysowanie tekstu i pól
        window.draw(inputText);
        window.draw(idText);
        window.draw(adresText);
        window.draw(wagaText);
        window.draw(xText);
        window.draw(yText);

        // Drawing input fields and their contents
        for (int i = 0; i < 5; ++i) {
            inputField.setPosition(150, 40 + i * 40);
            window.draw(inputField);

            sf::Text fieldText(inputBuffers[i], font, 20);
            fieldText.setPosition(155, 40 + i * 40);
            window.draw(fieldText);
        }

        // Drawing buttons
        window.draw(calculateGeneticButton);
        window.draw(geneticButtonText);
        window.draw(calculateGreedyButton);
        window.draw(greedyButtonText);
        window.draw(mapButton);
        window.draw(mapButtonText);

        // Display entered packages
        sf::Text packageDataText("Paczki:", font, 20);
        packageDataText.setPosition(10, 320);
        window.draw(packageDataText);

        for (size_t i = 0; i < paczki.size(); ++i) {
            sf::Text packageInfo(std::to_string(paczki[i].getId()) + ": " + paczki[i].getAdres(), font, 20);
            packageInfo.setPosition(10, 350 + i * 30);
            window.draw(packageInfo);
        }

        // Display calculated routes
        sf::Text routeTitle("Wyznaczone trasy:", font, 20);
        routeTitle.setPosition(10, 500);
        window.draw(routeTitle);

        for (size_t i = 0; i < routes.size(); ++i) {
            sf::Text routeInfo(routes[i], font, 20);
            routeInfo.setPosition(10, 530 + i * 30);
            window.draw(routeInfo);
        }

        window.display();

        // Map window
        if (showMap) {
            // sf::RenderWindow mapWindow(sf::VideoMode(800, 600), "Mapa paczek");
            // while (mapWindow.isOpen()) {
            //     sf::Event mapEvent;
            //     while (mapWindow.pollEvent(mapEvent)) {
            //         if (mapEvent.type == sf::Event::Closed) {
            //             mapWindow.close();
            //         }
            //     }

            //     mapWindow.clear(sf::Color::White);

            //     // Rysowanie paczek na mapie
            //     for (const auto& paczka : paczki) {
            //         sf::CircleShape point(5);
            //         point.setFillColor(sf::Color::Red);
            //         point.setPosition(paczka.getX() * 50, paczka.getY() * 50); // Zmniejszamy współrzędne dla widoczności
            //         mapWindow.draw(point);
            //     }

            //     mapWindow.display();
            // }
                // Okno mapy do wyświetlania siatki
    sf::RenderWindow mapWindow(sf::VideoMode(800, 600), "Mapa paczek", sf::Style::Close);

    while (mapWindow.isOpen()) {
        sf::Event event;
        while (mapWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mapWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(mapWindow);
                    if (mapButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Otwórz okno mapy
                        mapWindow.setVisible(true);
                    }
                }
            }
        }

        mapWindow.clear();
        mapWindow.draw(mapButton);
        mapWindow.draw(mapButtonText);

        window.display();

        // Rysowanie siatki i paczek w oknie mapy
        if (mapWindow.isOpen()) {
            while (mapWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    mapWindow.close();
                }
            }

            mapWindow.clear(sf::Color::White);

            // Rysowanie siatki
            sf::VertexArray gridLines(sf::Lines);
            float gridSize = 50.0f; // Odstęp między liniami siatki

            // Rysowanie poziomych linii siatki
            for (float y = 0; y < mapWindow.getSize().y; y += gridSize) {
                gridLines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(200, 200, 200)));
                gridLines.append(sf::Vertex(sf::Vector2f(mapWindow.getSize().x, y), sf::Color(200, 200, 200)));
            }

            // Rysowanie pionowych linii siatki
            for (float x = 0; x < mapWindow.getSize().x; x += gridSize) {
                gridLines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(200, 200, 200)));
                gridLines.append(sf::Vertex(sf::Vector2f(x, mapWindow.getSize().y), sf::Color(200, 200, 200)));
            }

            mapWindow.draw(gridLines);

            // Rysowanie osi
            sf::VertexArray axes(sf::Lines, 4);
            axes[0].position = sf::Vector2f(mapWindow.getSize().x / 2, 0); // Oś Y
            axes[1].position = sf::Vector2f(mapWindow.getSize().x / 2, mapWindow.getSize().y);
            axes[2].position = sf::Vector2f(0, mapWindow.getSize().y / 2); // Oś X
            axes[3].position = sf::Vector2f(mapWindow.getSize().x, mapWindow.getSize().y / 2);
            axes[0].color = axes[1].color = axes[2].color = axes[3].color = sf::Color::Black;
            mapWindow.draw(axes);

            // Rysowanie paczek
            for (const auto& paczka : paczki) {
                sf::CircleShape point(5);
                point.setFillColor(sf::Color::Red);
                // Skaluje współrzędne do rozmiaru okna
                point.setPosition(paczka.getX() * gridSize + mapWindow.getSize().x / 2, 
                                  mapWindow.getSize().y / 2 - paczka.getY() * gridSize);
                mapWindow.draw(point);
                

                // Rysowanie ID paczki obok punktu
                sf::Text idText(std::to_string(paczka.getId()), font, 15); // Tworzenie tekstu z ID paczki
                idText.setPosition(paczka.getX() * gridSize + mapWindow.getSize().x / 2 + 10, // Przesunięcie w prawo
                                mapWindow.getSize().y / 2 - paczka.getY() * gridSize - 10); // Przesunięcie w górę
                idText.setFillColor(sf::Color::Black); // Kolor tekstu
                mapWindow.draw(idText); // Rysowanie tekstu z ID paczki
            }

                        // Rysowanie magazynu
            sf::CircleShape warehousePoint(10); // Większy punkt dla magazynu
            warehousePoint.setFillColor(sf::Color::Green); // Kolor magazynu
            // Skaluje współrzędne magazynu do rozmiaru okna
            warehousePoint.setPosition(magazyn.getX() * gridSize + mapWindow.getSize().x / 2 - 10, 
                                    mapWindow.getSize().y / 2 - magazyn.getY() * gridSize - 10); // Ustawienie punktu w miejscu magazynu
            mapWindow.draw(warehousePoint);

            // Rysowanie ID magazynu
            sf::Text warehouseIdText("Magazyn", font, 15); // Tekst dla magazynu
            warehouseIdText.setPosition(magazyn.getX() * gridSize + mapWindow.getSize().x / 2 + 15, 
                                        mapWindow.getSize().y / 2 - magazyn.getY() * gridSize - 10); // Przesunięcie tekstu obok punktu magazynu
            warehouseIdText.setFillColor(sf::Color::Black); // Kolor tekstu
            mapWindow.draw(warehouseIdText); // Rysowanie tekstu z ID magazynu

                        // Rysowanie linii między punktami (trasą kuriera)
            if (!routes.empty()) {
                sf::VertexArray routeLines(sf::LinesStrip); // Używamy LinesStrip, aby rysować ciągłą linię
                routeLines.append(sf::Vertex(sf::Vector2f(magazyn.getX() * gridSize + mapWindow.getSize().x / 2, 
                                                        mapWindow.getSize().y / 2 - magazyn.getY() * gridSize), sf::Color::Blue)); // Magazyn jako początek trasy
                
                for (const auto& paczka : paczki) {
                    routeLines.append(sf::Vertex(sf::Vector2f(paczka.getX() * gridSize + mapWindow.getSize().x / 2, 
                                                            mapWindow.getSize().y / 2 - paczka.getY() * gridSize), sf::Color::Blue)); // Dodaj punkt paczki
                }

                mapWindow.draw(routeLines); // Rysowanie linii łączącej punkty
            }



            mapWindow.display();
        }
    }
            showMap = false; // Reset flag after closing the map window
        }
    }

    return 0;
}
