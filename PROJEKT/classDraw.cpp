#include "classDraw.h"
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classTrasa.h" // Include this for the Trasa class
#include <cmath>
#include <iostream>
#include "classHandlingEvents.h"

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

double classDraw::calculateDistance(double x1, double y1, double x2, double y2)
{
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void classDraw::MainWindow(sf::RenderWindow &window, sf::Font &font, std::vector<Paczka> &paczki, Magazyn &magazyn, Kurier &kurier, Mapa &mapa)
{
    auto uiElements = initializeUIElements(font); // Inicjalizacja interfejsu użytkownika
    std::vector<std::string> inputBuffers(5, ""); // Bufory wejściowe dla ID, Adres, Waga, X, Y
    int step = 0;                                 // Krok aktualnego pola wejściowego
    std::vector<std::string> routes;              // Lista tras
    bool showMap = false;
    classHandlingEvents classHandlingEvents;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Obsługa zdarzeń
            //handleMainWindowEvents(event, window, paczki, magazyn, kurier, mapa, routes, showMap, uiElements, inputBuffers, step);
            classHandlingEvents.handleMainWindowEvents(event, window, paczki, magazyn, kurier, mapa, routes, showMap, uiElements, inputBuffers, step);
        }
        // Rysowanie głównego okna
        drawMainWindow(window, font, paczki, routes, uiElements);
        if (showMap)
        {
            // Otwórz okno mapy
            showMapWindow(font, paczki, magazyn, routes);
            showMap = false;
        }
    }
}

// Inicjalizacja elementów interfejsu użytkownika

UIElements classDraw::initializeUIElements(sf::Font &font)
{
    UIElements elements;

    elements.inputText.setFont(font);
    elements.inputText.setString("Wprowadz dane paczki:");
    elements.inputText.setPosition(100, 10);
    elements.inputText.setCharacterSize(20);

    // Dodaj etykiety
    std::vector<std::string> labels = {
        "ID Paczki:",
        "Adres:",
        "Waga (kg):",
        "Wspolrzedna X:",
        "Wspolrzedna Y:"};

    for (size_t i = 0; i < labels.size(); ++i)
    {
        sf::Text label;
        label.setFont(font);
        label.setString(labels[i]);
        label.setCharacterSize(20);
        label.setPosition(10, 50 + i * 40); // Pozycjonowanie obok pól
        elements.inputLabels.push_back(label);

        sf::RectangleShape inputField(sf::Vector2f(1, 30));
        inputField.setFillColor(sf::Color::White);
        inputField.setPosition(150, 50 + i * 40); // Pozycjonowanie pól
        elements.inputFields.push_back(inputField);

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(20);
        inputText.setPosition(155, 50 + i * 40); // Pozycjonowanie tekstu w polach
        elements.inputTexts.push_back(inputText);
    }

    // Przyciski
    auto buttonGenetic = createButton(sf::Vector2f(10, 250), "alg. genetyczny", sf::Color::Green, font);
    elements.buttons["calculateGenetic"] = buttonGenetic.first;
    elements.buttonTexts["calculateGenetic"] = buttonGenetic.second;

    auto buttonGreedy = createButton(sf::Vector2f(220, 250), "alg. zachlanny", sf::Color::Blue, font);
    elements.buttons["calculateGreedy"] = buttonGreedy.first;
    elements.buttonTexts["calculateGreedy"] = buttonGreedy.second;

    auto buttonAnnealing = createButton(sf::Vector2f(430, 250), "alg. wyzarzania", sf::Color::Cyan, font);
    elements.buttons["calculateAnnealing"] = buttonAnnealing.first;
    elements.buttonTexts["calculateAnnealing"] = buttonAnnealing.second;

    auto buttonMap = createButton(sf::Vector2f(640, 10), "MAPA", sf::Color::Magenta, font);
    elements.buttons["map"] = buttonMap.first;
    elements.buttonTexts["map"] = buttonMap.second;

    auto buttonSelectFromMap = createButton(sf::Vector2f(640, 70), "Wybierz z mapy", sf::Color::Yellow, font);
    elements.buttons["selectFromMap"] = buttonSelectFromMap.first;
    elements.buttonTexts["selectFromMap"] = buttonSelectFromMap.second;

    return elements;
}


std::pair<sf::RectangleShape, sf::Text> classDraw::createButton(const sf::Vector2f &position, const std::string &text, const sf::Color &color, sf::Font &font)
{
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(position);
    button.setFillColor(color);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(position.x + 10, position.y + 10);

    return {button, buttonText};
}



// Rysowanie głównego okna

void classDraw::drawMainWindow(sf::RenderWindow &window, sf::Font &font, std::vector<Paczka> &paczki, std::vector<std::string> &routes, UIElements &uiElements)
{
    window.clear();
    drawUIElements(window, uiElements);

    // Rysowanie pól tekstowych i ich zawartości
    for (size_t i = 0; i < uiElements.inputFields.size(); ++i)
    {
        // Rysowanie prostokątów pól
        window.draw(uiElements.inputFields[i]);

        // Rysowanie tekstu w polach
        window.draw(uiElements.inputTexts[i]);
    }

    drawPackages(window, font, paczki); // Rysowanie paczek

    // Wyświetlanie tytułu sekcji tras
    sf::Text routeTitle("Wyznaczone trasy:", font, 20);
    routeTitle.setPosition(10, 500);
    window.draw(routeTitle);

    drawRoutes(window, font, routes); // Rysowanie tras

    window.display();
}


void classDraw::drawUIElements(sf::RenderWindow &window, UIElements &uiElements)
{
    // Rysowanie tytułu
    window.draw(uiElements.inputText);

    // Rysowanie etykiet i pól wejściowych
    for (size_t i = 0; i < uiElements.inputFields.size(); ++i)
    {
        window.draw(uiElements.inputLabels[i]); // Rysowanie etykiety
        window.draw(uiElements.inputFields[i]); // Rysowanie pola wejściowego
        window.draw(uiElements.inputTexts[i]);  // Rysowanie tekstu w polu
    }

    // Rysowanie przycisków i ich tekstów
    for (auto &[key, button] : uiElements.buttons)
    {
        window.draw(button);
        window.draw(uiElements.buttonTexts[key]);
    }
}

void classDraw::drawPackages(sf::RenderWindow &window, sf::Font &font, std::vector<Paczka> &paczki)
{
    sf::Text packageText("", font, 20);
    packageText.setPosition(10, 300);
    for (size_t i = 0; i < paczki.size(); ++i)
    {
        packageText.setString("Paczka " + std::to_string(paczki[i].getId()) + ": " + paczki[i].getAdres());
        packageText.move(0, 30); // Move down for each package
        window.draw(packageText);
    }
}

void classDraw::drawRoutes(sf::RenderWindow &window, sf::Font &font, std::vector<std::string> &routes)
{
    if (routes.empty())
    {
        return; // Jeśli brak tras, nic nie wyświetlaj
    }

    // Tytuł sekcji tras
    sf::Text routeTitle("Wyznaczone trasy:", font, 20);
    routeTitle.setPosition(10, 500);
    window.draw(routeTitle);

    // Pozycjonowanie początkowe dla listy tras
    sf::Text routeText("", font, 20);
    routeText.setPosition(10, 530); // Start poniżej tytułu

    // Iteracja przez kolejne trasy i wyświetlanie
    for (const auto &route : routes)
    {
        routeText.setString(route);
        window.draw(routeText);
        routeText.move(0, 30); // Przesunięcie w dół dla kolejnej linii
    }
}



// Rysowanie mapy

void classDraw::showMapWindow(sf::Font &font, std::vector<Paczka> &paczki, Magazyn &magazyn, std::vector<std::string> &routes)
{
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow mapWindow(fullScreenMode, "Mapa paczek", sf::Style::Default);

    while (mapWindow.isOpen())
    {
        sf::Event event; // Deklaracja zmiennej event
        while (mapWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mapWindow.close();
            }

            // Obsługa kliknięcia na mapę, gdy flaga selectingFromMap jest włączona
            if (selectingFromMap && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Oblicz współrzędne kliknięcia
                float clickedX = (event.mouseButton.x - mapWindow.getSize().x / 2) / 50.0f;
                float clickedY = (mapWindow.getSize().y / 2 - event.mouseButton.y) / 50.0f;

                // Otwórz okno szczegółów paczki
                addPackageDetails(font, paczki, clickedX, clickedY);

                selectingFromMap = false; // Wyłącz tryb wybierania z mapy
                mapWindow.close(); // Zamknij mapę po wybraniu punktu
            }
        }

        // Rysowanie mapy
        mapWindow.clear(sf::Color::White);
        drawMapWindow(mapWindow, font, paczki, magazyn, routes);
        if (!currentRoute.empty())
        {
            drawRoutesOnMap(mapWindow, magazyn, currentRoute); // Rysowanie aktualnej trasy
        }
        mapWindow.display();
    }
}



void classDraw::addPackageDetails(sf::Font &font, std::vector<Paczka> &paczki, float x, float y)
{
    sf::RenderWindow detailWindow(sf::VideoMode(400, 300), "Dodaj szczegoly paczki");

    // Etykiety
    sf::Text idLabel("ID Paczki:", font, 20);
    idLabel.setPosition(20, 20);

    sf::Text adresLabel("Adres:", font, 20);
    adresLabel.setPosition(20, 80);

    sf::Text wagaLabel("Waga (kg):", font, 20);
    wagaLabel.setPosition(20, 140);

    sf::Text wspolrzedneLabel("Wspolrzedne: (" + std::to_string(x) + ", " + std::to_string(y) + ")", font, 20);
    wspolrzedneLabel.setPosition(20, 200);

    // Pola tekstowe
    std::vector<std::string> inputBuffers(2, ""); // Bufory dla ID i Adresu
    int step = 0; // Aktualnie edytowane pole

    sf::RectangleShape inputField(sf::Vector2f(300, 30));
    inputField.setFillColor(sf::Color::White);
    inputField.setOutlineThickness(1);
    inputField.setOutlineColor(sf::Color::Black);

    while (detailWindow.isOpen())
    {
        sf::Event event;
        while (detailWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                detailWindow.close();

            if (event.type == sf::Event::TextEntered && step < 2)
            {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (enteredChar == '\b') // Backspace
                {
                    if (!inputBuffers[step].empty())
                        inputBuffers[step].pop_back();
                }
                else if (enteredChar >= 32 && enteredChar <= 126) // Printable characters
                {
                    inputBuffers[step] += enteredChar;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (step == 1) // Ostatnie pole
                {
                    // Dodaj paczkę do listy
                    int paczkaId = std::stoi(inputBuffers[0]);
                    std::string adres = inputBuffers[1];
                    double waga = 0.0; // Default weight (can be changed)
                    paczki.emplace_back(paczkaId, adres, waga, x, y);

                    detailWindow.close(); // Zamknij okno po dodaniu paczki
                }
                else
                {
                    step++;
                }
            }
        }

        detailWindow.clear(sf::Color::White);

        // Rysowanie etykiet
        detailWindow.draw(idLabel);
        detailWindow.draw(adresLabel);
        detailWindow.draw(wagaLabel);
        detailWindow.draw(wspolrzedneLabel);

        // Rysowanie pola aktywnego
        inputField.setPosition(20, 20 + step * 60);
        detailWindow.draw(inputField);

        // Wyświetlanie tekstu w polach
        for (int i = 0; i < 2; ++i)
        {
            sf::Text fieldText(inputBuffers[i], font, 20);
            fieldText.setPosition(25, 25 + i * 60);
            fieldText.setFillColor(sf::Color::Black);
            detailWindow.draw(fieldText);
        }

        detailWindow.display();
    }
}


void classDraw::drawMapWindow(sf::RenderWindow &mapWindow, sf::Font &font, std::vector<Paczka> &paczki, Magazyn &magazyn, std::vector<std::string> &routes) 
{
    mapWindow.clear(sf::Color::White);

    drawGrid(mapWindow);
    drawAxis(mapWindow);
    drawPackagesOnMap(mapWindow, font, paczki);
    drawWarehouse(mapWindow, font, magazyn);
}

void classDraw::drawGrid(sf::RenderWindow &mapWindow)
{
    sf::VertexArray gridLines(sf::Lines);
    float gridSize = 50.0f;
    float centerX = mapWindow.getSize().x / 2.0f;
    float centerY = mapWindow.getSize().y / 2.0f;

    // Rysowanie poziomych linii (Y)
    for (float y = centerY; y >= 0; y -= gridSize)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(mapWindow.getSize().x, y), sf::Color(200, 200, 200)));
    }
    for (float y = centerY; y <= mapWindow.getSize().y; y += gridSize)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(mapWindow.getSize().x, y), sf::Color(200, 200, 200)));
    }

    // Rysowanie pionowych linii (X)
    for (float x = centerX; x >= 0; x -= gridSize)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(x, mapWindow.getSize().y), sf::Color(200, 200, 200)));
    }
    for (float x = centerX; x <= mapWindow.getSize().x; x += gridSize)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(x, mapWindow.getSize().y), sf::Color(200, 200, 200)));
    }

    // Rysowanie siatki na oknie
    mapWindow.draw(gridLines);
}

void classDraw::drawAxis(sf::RenderWindow &mapWindow)
{
    // Example implementation for drawing axes
    sf::VertexArray axes(sf::Lines, 4);
    float centerX = mapWindow.getSize().x / 2;
    float centerY = mapWindow.getSize().y / 2;

    axes[0].position = sf::Vector2f(centerX, 0); // Y-axis
    axes[1].position = sf::Vector2f(centerX, mapWindow.getSize().y);
    axes[2].position = sf::Vector2f(0, centerY); // X-axis
    axes[3].position = sf::Vector2f(mapWindow.getSize().x, centerY);

    axes[0].color = axes[1].color = axes[2].color = axes[3].color = sf::Color::Black;

    mapWindow.draw(axes);
}

void classDraw::drawPackagesOnMap(sf::RenderWindow &mapWindow, sf::Font &font, std::vector<Paczka> &paczki)
{
    // Example implementation for drawing packages
    for (const auto &paczka : paczki)
    {
        sf::CircleShape point(5);
        point.setFillColor(sf::Color::Red);

        // Convert package coordinates to window coordinates
        float pixelX = paczka.getX() * 50 + mapWindow.getSize().x / 2;
        float pixelY = mapWindow.getSize().y / 2 - paczka.getY() * 50;

        point.setPosition(pixelX - 5, pixelY - 5); // Adjust for circle center
        mapWindow.draw(point);

        // Draw package ID
        sf::Text idText(std::to_string(paczka.getId()), font, 15);
        idText.setPosition(pixelX + 10, pixelY - 10);
        idText.setFillColor(sf::Color::Black);
        mapWindow.draw(idText);
    }
}

void classDraw::drawWarehouse(sf::RenderWindow &mapWindow, sf::Font &font, Magazyn &magazyn)
{
    // Example implementation for drawing the warehouse
    sf::CircleShape warehousePoint(10);
    warehousePoint.setFillColor(sf::Color::Green);

    // Convert warehouse coordinates to window coordinates
    float warehouseX = magazyn.getX() * 50 + mapWindow.getSize().x / 2;
    float warehouseY = mapWindow.getSize().y / 2 - magazyn.getY() * 50;

    warehousePoint.setPosition(warehouseX - 10, warehouseY - 10); // Adjust for circle center
    mapWindow.draw(warehousePoint);

    // Draw warehouse label
    sf::Text warehouseText("Magazyn", font, 15);
    warehouseText.setPosition(warehouseX + 15, warehouseY - 10);
    warehouseText.setFillColor(sf::Color::Black);
    mapWindow.draw(warehouseText);
}


void classDraw::drawRoutesOnMap(sf::RenderWindow &mapWindow, Magazyn &magazyn, const std::vector<Paczka> &optimalRoute)
{
    if (optimalRoute.empty())
        return; // Jeśli brak punktów w trasie, nic nie rysujemy

    sf::VertexArray routeLines(sf::LinesStrip);

    // Start od magazynu
    float prevX = magazyn.getX();
    float prevY = magazyn.getY();

    // Dodaj magazyn jako pierwszy punkt trasy
    float startX = prevX * 50 + mapWindow.getSize().x / 2.0f;
    float startY = mapWindow.getSize().y / 2.0f - prevY * 50;
    routeLines.append(sf::Vertex(sf::Vector2f(startX, startY), sf::Color::Blue));

    // Iteracja przez punkty w trasie
    for (const auto &paczka : optimalRoute)
    {
        // Oblicz współrzędne kolejnego punktu
        float pixelX = paczka.getX() * 50 + mapWindow.getSize().x / 2.0f;
        float pixelY = mapWindow.getSize().y / 2.0f - paczka.getY() * 50;

        // Dodaj punkt do linii
        routeLines.append(sf::Vertex(sf::Vector2f(pixelX, pixelY), sf::Color::Blue));
    }

    // Dodaj powrót do magazynu
    float endX = magazyn.getX() * 50 + mapWindow.getSize().x / 2.0f;
    float endY = mapWindow.getSize().y / 2.0f - magazyn.getY() * 50;
    routeLines.append(sf::Vertex(sf::Vector2f(endX, endY), sf::Color::Blue));

    // Rysowanie linii
    mapWindow.draw(routeLines);
}

