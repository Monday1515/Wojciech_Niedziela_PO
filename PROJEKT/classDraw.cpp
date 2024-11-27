#include "classDraw.h"
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classTrasa.h" // Include this for the Trasa class
#include <cmath>
#include <iostream>

// Konstruktor klasy
classDraw::classDraw() {}

// Implementacja metody MagazynInput
void classDraw::MagazynInput(sf::Font &font, std::vector<std::string> &magazynInputBuffers, int &magazynStep, double &magazynX, double &magazynY)
{
    sf::RenderWindow inputWindow(sf::VideoMode(400, 300), "Wprowadz lokalizacje magazynu");

    sf::Text instructionText("Wprowadz wspolrzedne magazynu:", font, 20);
    instructionText.setPosition(20, 20);

    sf::Text xLabel("X:", font, 20);
    xLabel.setPosition(20, 80);

    sf::Text yLabel("Y:", font, 20);
    yLabel.setPosition(20, 140);

    sf::RectangleShape magazynInputField(sf::Vector2f(1, 30));
    magazynInputField.setFillColor(sf::Color::White);

    while (inputWindow.isOpen())
    {
        sf::Event event;
        while (inputWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                inputWindow.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && magazynStep < 2)
                {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == 8) // Backspace
                    {
                        if (!magazynInputBuffers[magazynStep].empty())
                            magazynInputBuffers[magazynStep].pop_back();
                    }
                    else
                    {
                        magazynInputBuffers[magazynStep] += enteredChar;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (magazynStep == 0)
                {
                    magazynX = std::stod(magazynInputBuffers[magazynStep]);
                }
                else if (magazynStep == 1)
                {
                    magazynY = std::stod(magazynInputBuffers[magazynStep]);
                    inputWindow.close();
                }
                magazynStep++;
                if (magazynStep > 1)
                    magazynStep = 1;
            }
        }

        inputWindow.clear();
        inputWindow.draw(instructionText);
        inputWindow.draw(xLabel);
        inputWindow.draw(yLabel);

        for (int i = 0; i < 2; ++i)
        {
            magazynInputField.setPosition(60, 80 + i * 60);
            inputWindow.draw(magazynInputField);

            sf::Text fieldText(magazynInputBuffers[i], font, 20);
            fieldText.setPosition(65, 80 + i * 60);
            inputWindow.draw(fieldText);
        }

        inputWindow.display();
    }
}

double calculateDistance(double x1, double y1, double x2, double y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

void classDraw::MainWindow(
    sf::RenderWindow& window,
    sf::Font& font,
    std::vector<Paczka>& paczki,
    Magazyn& magazyn,
    Kurier& kurier,
    Mapa& mapa
) {
    // // Text Fields and Buttons Definitions
    // sf::Text inputText("Wprowadz dane paczki:", font, 20);
    // inputText.setPosition(100, 10);

    // sf::Text idText("ID Paczki:", font, 20);
    // idText.setPosition(10, 40);

    // sf::Text adresText("Adres:", font, 20);
    // adresText.setPosition(10, 80);

    // sf::Text wagaText("Waga (kg):", font, 20);
    // wagaText.setPosition(10, 120);

    // sf::Text xText("Wspolrzedna X:", font, 20);
    // xText.setPosition(10, 160);

    // sf::Text yText("Wspolrzedna Y:", font, 20);
    // yText.setPosition(10, 200);

    // sf::RectangleShape inputField(sf::Vector2f(300, 30));
    // inputField.setFillColor(sf::Color::White);

    // sf::RectangleShape calculateGeneticButton(sf::Vector2f(200, 50));
    // calculateGeneticButton.setPosition(10, 250);
    // calculateGeneticButton.setFillColor(sf::Color::Green);

    // sf::Text geneticButtonText("alg. genetyczny", font, 20);
    // geneticButtonText.setPosition(15, 260);

    // sf::RectangleShape calculateGreedyButton(sf::Vector2f(200, 50));
    // calculateGreedyButton.setPosition(220, 250);
    // calculateGreedyButton.setFillColor(sf::Color::Blue);

    // sf::Text greedyButtonText("alg. zachlanny", font, 20);
    // greedyButtonText.setPosition(225, 260);

    // sf::RectangleShape calculateAnnealingButton(sf::Vector2f(200, 50));
    // calculateAnnealingButton.setPosition(430, 250);
    // calculateAnnealingButton.setFillColor(sf::Color::Cyan);

    // sf::Text annealingButtonText("alg. wyzarzania", font, 20);
    // annealingButtonText.setPosition(435, 260);

    // sf::RectangleShape mapButton(sf::Vector2f(200, 50));
    // mapButton.setPosition(640, 10);
    // mapButton.setFillColor(sf::Color::Magenta);

    // sf::Text mapButtonText("MAPA", font, 20);
    // mapButtonText.setPosition(660, 20);

    // // Buffers and Variables
    // std::vector<std::string> inputBuffers(5, "");
    // int step = 0;
    // int paczkaId;
    // std::string adres;
    // double waga, x, y;
    // bool showMap = false;
    // std::vector<std::string> routes;

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();

    //         if (event.type == sf::Event::TextEntered && step < 5) {
    //             char enteredChar = static_cast<char>(event.text.unicode);
    //             if (enteredChar == '\b' && !inputBuffers[step].empty()) { // Backspace
    //                 inputBuffers[step].pop_back();
    //             } else if (enteredChar >= 32 && enteredChar <= 126) {
    //                 inputBuffers[step] += enteredChar;
    //             }
    //         }

    //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
    //             switch (step) {
    //                 case 0: paczkaId = std::stoi(inputBuffers[step]); break;
    //                 case 1: adres = inputBuffers[step]; break;
    //                 case 2: waga = std::stod(inputBuffers[step]); break;
    //                 case 3: x = std::stod(inputBuffers[step]); break;
    //                 case 4:
    //                     y = std::stod(inputBuffers[step]);
    //                     paczki.emplace_back(paczkaId, adres, waga, x, y);
    //                     inputBuffers = std::vector<std::string>(5, ""); // Reset buffers
    //                     step = -1; // Reset step
    //                     break;
    //             }
    //             step++;
    //         }

    //         if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
    //             sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    //             if (calculateGeneticButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
    //                 Trasa trasa(&kurier, &magazyn, paczki, &mapa);
    //                 auto optimalRouteGenetic = trasa.znajdzTraseAlgorytmGenetyczny();
    //                 routes.clear();
    //                 double totalDistance = 0.0, prevX = magazyn.getX(), prevY = magazyn.getY();
    //                 for (const auto& paczka : optimalRouteGenetic) {
    //                     double dist = std::hypot(paczka.getX() - prevX, paczka.getY() - prevY);
    //                     totalDistance += dist;
    //                     routes.push_back("Dostawa: " + paczka.getAdres());
    //                     prevX = paczka.getX();
    //                     prevY = paczka.getY();
    //                 }
    //                 totalDistance += std::hypot(prevX - magazyn.getX(), prevY - magazyn.getY());
    //                 routes.push_back("Powrót do magazynu");
    //                 routes.push_back("Całkowita długość trasy: " + std::to_string(totalDistance) + " jednostek");
    //             }

    //             if (mapButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
    //                 showMap = true;
    //             }
    //         }
    //     }

    //     // // Draw Window Elements
    //     // window.clear();
    //     // window.draw(inputText);
    //     // window.draw(idText);
    //     // window.draw(adresText);
    //     // window.draw(wagaText);
    //     // window.draw(xText);
    //     // window.draw(yText);
    //     // window.draw(calculateGeneticButton);
    //     // window.draw(geneticButtonText);
    //     // window.draw(mapButton);
    //     // window.draw(mapButtonText);

    //     // // Draw Routes
    //     // for (size_t i = 0; i < routes.size(); ++i) {
    //     //     sf::Text routeInfo(routes[i], font, 20);
    //     //     routeInfo.setPosition(10, 500 + i * 30);
    //     //     window.draw(routeInfo);
    //     // }

    //     // window.display();

    //     window.clear();

    //     // Rysowanie tekstu i pól
    //     window.draw(inputText);
    //     window.draw(idText);
    //     window.draw(adresText);
    //     window.draw(wagaText);
    //     window.draw(xText);
    //     window.draw(yText);

    //     // Drawing input fields and their contents
    //     for (int i = 0; i < 5; ++i)
    //     {
    //         inputField.setPosition(150, 40 + i * 40);
    //         window.draw(inputField);

    //         sf::Text fieldText(inputBuffers[i], font, 20);
    //         fieldText.setPosition(155, 40 + i * 40);
    //         window.draw(fieldText);
    //     }

    //     // Drawing buttons
    //     window.draw(calculateGeneticButton);
    //     window.draw(geneticButtonText);
    //     window.draw(calculateGreedyButton);
    //     window.draw(greedyButtonText);
    //     window.draw(calculateAnnealingButton);
    //     window.draw(annealingButtonText);
    //     window.draw(mapButton);
    //     window.draw(mapButtonText);

    //     // Display entered packages
    //     sf::Text packageDataText("Paczki:", font, 20);
    //     packageDataText.setPosition(10, 320);
    //     window.draw(packageDataText);

    //     for (size_t i = 0; i < paczki.size(); ++i)
    //     {
    //         sf::Text packageInfo(std::to_string(paczki[i].getId()) + ": " + paczki[i].getAdres(), font, 20);
    //         packageInfo.setPosition(10, 350 + i * 30);
    //         window.draw(packageInfo);
    //     }

    //     // Display calculated routes
    //     sf::Text routeTitle("Wyznaczone trasy:", font, 20);
    //     routeTitle.setPosition(10, 500);
    //     window.draw(routeTitle);

    //     for (size_t i = 0; i < routes.size(); ++i)
    //     {
    //         sf::Text routeInfo(routes[i], font, 20);
    //         routeInfo.setPosition(10, 530 + i * 30);
    //         window.draw(routeInfo);
    //     }

    //     window.display();

    //     // Show Map if Requested
    //     if (showMap) {
    //         sf::RenderWindow mapWindow(sf::VideoMode::getDesktopMode(), "Mapa paczek", sf::Style::Default);
    //         while (mapWindow.isOpen()) {
    //             sf::Event mapEvent;
    //             while (mapWindow.pollEvent(mapEvent)) {
    //                 if (mapEvent.type == sf::Event::Closed)
    //                     mapWindow.close();
    //             }

    //             mapWindow.clear(sf::Color::White);
    //             // Draw Grid, Axes, and Routes Here (similar to the earlier logic)
    //             mapWindow.display();
    //         }
    //         showMap = false;
    //     }
    // }

    // aaaaaaaaaaaaaaa

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

    sf::RectangleShape calculateAnnealingButton(sf::Vector2f(200, 50));
    calculateAnnealingButton.setPosition(430, 250);
    calculateAnnealingButton.setFillColor(sf::Color::Cyan);

    sf::Text AnnealingButtonText("alg. wyzarzania", font, 20);
    AnnealingButtonText.setPosition(435, 260);
    AnnealingButtonText.setFillColor(sf::Color::White);

    // Tworzenie przycisku "MAPA"
    sf::RectangleShape mapButton(sf::Vector2f(200, 50));
    mapButton.setPosition(640, 10);
    mapButton.setFillColor(sf::Color::Magenta);

    sf::Text mapButtonText("MAPA", font, 20);
    mapButtonText.setPosition(660, 20);
    mapButtonText.setFillColor(sf::Color::White);

    // Buffers for inputs
    std::vector<std::string> inputBuffers(5, ""); // Buffers for ID, Address, Weight, X, Y
    int step = 0;                                 // Step tracker for the current field
    int paczkaId;
    std::string adres;
    double waga, x, y;

    // Store calculated routes
    std::vector<std::string> routes;

    bool showMap = false; // Flag to indicate if the map window should be shown

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && step < 5)
                {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == 8)
                    { // Backspace
                        if (!inputBuffers[step].empty())
                            inputBuffers[step].pop_back();
                    }
                    else
                    {
                        inputBuffers[step] += enteredChar;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                switch (step)
                {
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
                    step = -1;                                      // Zresetuj krok
                    break;
                }
                step++;
                if (step > 4)
                    step = 4; // Ensure step does not exceed the last input field
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (calculateGeneticButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        // Wyznaczanie tras algorytmem genetycznym
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        auto optimalRouteGenetic = trasa.znajdzTraseAlgorytmGenetyczny();
                        routes.clear();

                        double totalDistance = 0.0;
                        double prevX = magazyn.getX(), prevY = magazyn.getY();

                        for (const auto &paczka : paczki)
                        {
                            double dist = calculateDistance(prevX, prevY, paczka.getX(), paczka.getY());
                            totalDistance += dist;
                            prevX = paczka.getX();
                            prevY = paczka.getY();
                            routes.push_back("Dostawa: " + paczka.getAdres());
                        }

                        totalDistance += calculateDistance(prevX, prevY, magazyn.getX(), magazyn.getY());
                        routes.push_back("Powrot do magazynu");
                        routes.push_back("Calkowita dlugosc trasy: " + std::to_string(totalDistance) + " jednostek");
                    }

                    if (calculateGreedyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        // Wyznaczanie tras algorytmem zachłannym
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        auto optimalRouteGreedy = trasa.znajdzTraseAlgorytmZachlanny();
                        routes.clear();

                        double totalDistance = 0.0;
                        double prevX = magazyn.getX(), prevY = magazyn.getY();

                        for (const auto &paczka : paczki)
                        {
                            double dist = calculateDistance(prevX, prevY, paczka.getX(), paczka.getY());
                            totalDistance += dist;
                            prevX = paczka.getX();
                            prevY = paczka.getY();
                            routes.push_back("Dostawa: " + paczka.getAdres());
                        }

                        totalDistance += calculateDistance(prevX, prevY, magazyn.getX(), magazyn.getY());
                        routes.push_back("Powrot do magazynu");
                        routes.push_back("Calkowita dlugosc trasy: " + std::to_string(totalDistance) + " jednostek");
                    }

                    if (calculateAnnealingButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        // Wyznaczanie tras algorytmem zachłannym
                        Trasa trasa(&kurier, &magazyn, paczki, &mapa);
                        auto optimalRouteAnnealing = trasa.znajdzTraseWyzarzanie();
                        routes.clear();

                        double totalDistance = 0.0;
                        double prevX = magazyn.getX(), prevY = magazyn.getY();

                        for (const auto &paczka : paczki)
                        {
                            double dist = calculateDistance(prevX, prevY, paczka.getX(), paczka.getY());
                            totalDistance += dist;
                            prevX = paczka.getX();
                            prevY = paczka.getY();
                            routes.push_back("Dostawa: " + paczka.getAdres());
                        }

                        totalDistance += calculateDistance(prevX, prevY, magazyn.getX(), magazyn.getY());
                        routes.push_back("Powrot do magazynu");
                        routes.push_back("Calkowita dlugosc trasy: " + std::to_string(totalDistance) + " jednostek");
                    }

                    if (mapButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
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
        for (int i = 0; i < 5; ++i)
        {
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
        window.draw(calculateAnnealingButton);
        window.draw(AnnealingButtonText);
        window.draw(mapButton);
        window.draw(mapButtonText);

        // Display entered packages
        sf::Text packageDataText("Paczki:", font, 20);
        packageDataText.setPosition(10, 320);
        window.draw(packageDataText);

        for (size_t i = 0; i < paczki.size(); ++i)
        {
            sf::Text packageInfo(std::to_string(paczki[i].getId()) + ": " + paczki[i].getAdres(), font, 20);
            packageInfo.setPosition(10, 350 + i * 30);
            window.draw(packageInfo);
        }

        // Display calculated routes
        sf::Text routeTitle("Wyznaczone trasy:", font, 20);
        routeTitle.setPosition(10, 500);
        window.draw(routeTitle);

        for (size_t i = 0; i < routes.size(); ++i)
        {
            sf::Text routeInfo(routes[i], font, 20);
            routeInfo.setPosition(10, 530 + i * 30);
            window.draw(routeInfo);
        }

        window.display();

        //Map window
        if (showMap)
        {
            sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
            sf::RenderWindow mapWindow(fullScreenMode, "Mapa paczek", sf::Style::Default);

            while (mapWindow.isOpen())
            {
                sf::Event event;
                while (mapWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        mapWindow.close();
                    }

                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(mapWindow);
                            if (mapButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                            {
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
                if (mapWindow.isOpen())
                {
                    while (mapWindow.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            mapWindow.close();
                        }
                    }

                    mapWindow.clear(sf::Color::White);

                    // Rysowanie siatki
                    sf::VertexArray gridLines(sf::Lines);
                    // Rozmiar kratki
                    float gridSize = 50.0f;

                    // Wyśrodkowanie siatki w oknie (punktem odniesienia jest środek okna)
                    float centerX = mapWindow.getSize().x / 2;
                    float centerY = mapWindow.getSize().y / 2;

                    // Rysowanie siatki
                    //sf::VertexArray gridLines(sf::Lines);

                    // Rysowanie poziomych linii siatki
                    for (float y = centerY; y >= 0; y -= gridSize)
                    { // W górę
                        gridLines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(200, 200, 200)));
                        gridLines.append(sf::Vertex(sf::Vector2f(mapWindow.getSize().x, y), sf::Color(200, 200, 200)));
                    }
                    for (float y = centerY + gridSize; y <= mapWindow.getSize().y; y += gridSize)
                    { // W dół
                        gridLines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(200, 200, 200)));
                        gridLines.append(sf::Vertex(sf::Vector2f(mapWindow.getSize().x, y), sf::Color(200, 200, 200)));
                    }

                    // Rysowanie pionowych linii siatki
                    for (float x = centerX; x >= 0; x -= gridSize)
                    { // W lewo
                        gridLines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(200, 200, 200)));
                        gridLines.append(sf::Vertex(sf::Vector2f(x, mapWindow.getSize().y), sf::Color(200, 200, 200)));
                    }
                    for (float x = centerX + gridSize; x <= mapWindow.getSize().x; x += gridSize)
                    { // W prawo
                        gridLines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(200, 200, 200)));
                        gridLines.append(sf::Vertex(sf::Vector2f(x, mapWindow.getSize().y), sf::Color(200, 200, 200)));
                    }

                    // Rysowanie siatki
                    mapWindow.draw(gridLines);

                    // Rysowanie osi układu współrzędnych
                    sf::VertexArray axes(sf::Lines, 4);
                    axes[0].position = sf::Vector2f(centerX, 0); // Oś Y
                    axes[1].position = sf::Vector2f(centerX, mapWindow.getSize().y);
                    axes[2].position = sf::Vector2f(0, centerY); // Oś X
                    axes[3].position = sf::Vector2f(mapWindow.getSize().x, centerY);
                    axes[0].color = axes[1].color = axes[2].color = axes[3].color = sf::Color::Black;
                    mapWindow.draw(axes);

                    // Rysowanie paczek
                    for (const auto &paczka : paczki)
                    {
                        sf::CircleShape point(5);
                        point.setFillColor(sf::Color::Red);

                        // Przesuwanie współrzędnych na siatkę
                        float pixelX = paczka.getX() * gridSize + mapWindow.getSize().x / 2;
                        float pixelY = mapWindow.getSize().y / 2 - paczka.getY() * gridSize;

                        // Dopasowanie do siatki
                        point.setPosition(pixelX - 5, pixelY - 5);
                        mapWindow.draw(point);

                        // Rysowanie ID paczki obok punktu
                        sf::Text idText(std::to_string(paczka.getId()), font, 15);
                        idText.setPosition(pixelX + 10, pixelY - 10);
                        idText.setFillColor(sf::Color::Black);
                        mapWindow.draw(idText);
                    }

                    // Rysowanie magazynu
                    sf::CircleShape warehousePoint(10);
                    warehousePoint.setFillColor(sf::Color::Green);

                    // Przesuwanie współrzędnych magazynu na siatkę
                    float warehouseX = magazyn.getX() * gridSize + mapWindow.getSize().x / 2;
                    float warehouseY = mapWindow.getSize().y / 2 - magazyn.getY() * gridSize;

                    // Dopasowanie do siatki
                    warehousePoint.setPosition(warehouseX - 10, warehouseY - 10);
                    mapWindow.draw(warehousePoint);

                    // Rysowanie etykiety magazynu
                    sf::Text warehouseIdText("Magazyn", font, 15);
                    warehouseIdText.setPosition(warehouseX + 15, warehouseY - 10);
                    warehouseIdText.setFillColor(sf::Color::Black);
                    mapWindow.draw(warehouseIdText);

                    // Rysowanie linii tras
                    if (!routes.empty())
                    {
                        sf::VertexArray routeLines(sf::LinesStrip);
                        routeLines.append(sf::Vertex(sf::Vector2f(warehouseX, warehouseY), sf::Color::Blue));

                        for (const auto &paczka : paczki)
                        {
                            float routeX = paczka.getX() * gridSize + mapWindow.getSize().x / 2;
                            float routeY = mapWindow.getSize().y / 2 - paczka.getY() * gridSize;
                            routeLines.append(sf::Vertex(sf::Vector2f(routeX, routeY), sf::Color::Blue));
                        }

                        routeLines.append(sf::Vertex(sf::Vector2f(warehouseX, warehouseY), sf::Color::Blue));
                        mapWindow.draw(routeLines);
                    }

                    mapWindow.display();
                }
            }
            showMap = false; // Reset flag after closing the map window
        }
    }




}