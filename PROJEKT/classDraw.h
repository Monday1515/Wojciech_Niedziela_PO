#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"

class Paczka;
class Magazyn;
class Kurier;
class Mapa;

struct UIElements
{
    sf::Text inputText;
    std::vector<sf::RectangleShape> inputFields;       // Pola wejściowe
    std::vector<sf::Text> inputTexts;                  // Teksty wprowadzane
    std::vector<sf::Text> inputLabels;                 // Etykiety dla pól wejściowych
    std::map<std::string, sf::RectangleShape> buttons; // Przycisk mapowany na nazwy
    std::map<std::string, sf::Text> buttonTexts;       // Teksty na przyciskach
};

class classDraw
{
public:
    // Konstruktor domyślny
    classDraw();

    // Funkcja do wprowadzania współrzędnych magazynu
    void MagazynInput(sf::Font &font, std::vector<std::string> &magazynInputBuffers, int &magazynStep, double &magazynX, double &magazynY);

    void MainWindow(
        sf::RenderWindow &window,
        sf::Font &font,
        std::vector<Paczka> &paczki,
        Magazyn &magazyn,
        Kurier &kurier,
        Mapa &mapa);

    //void handleTextInput(sf::Event &event, std::vector<std::string> &inputBuffers, int &step, UIElements &uiElements);

    //void handleMouseClick(sf::Event &event, std::vector<Paczka> &paczki, Magazyn &magazyn, Kurier &kurier, Mapa &mapa, std::vector<std::string> &routes, bool &showMap, UIElements &uiElements);

    UIElements initializeUIElements(sf::Font &font);

    void drawUIElements(sf::RenderWindow &window, UIElements &uiElements);
    void drawPackages(sf::RenderWindow &window, sf::Font &font, std::vector<Paczka> &paczki);
    void drawRoutes(sf::RenderWindow &window, sf::Font &font, std::vector<std::string> &routes);

    void showMapWindow(sf::Font &font, std::vector<Paczka> &paczki, Magazyn &magazyn, std::vector<std::string> &routes);

    void drawMapWindow(sf::RenderWindow &mapWindow, sf::Font &font, std::vector<Paczka> &paczki, Magazyn &magazyn, std::vector<std::string> &routes);

    void drawGrid(sf::RenderWindow &mapWindow);
    void drawAxis(sf::RenderWindow &mapWindow);
    void drawPackagesOnMap(sf::RenderWindow &mapWindow, sf::Font &font, std::vector<Paczka> &paczki);
    void drawWarehouse(sf::RenderWindow &mapWindow, sf::Font &font, Magazyn &magazyn);
    void drawRoutesOnMap(sf::RenderWindow &mapWindow, Magazyn &magazyn, const std::vector<Paczka> &optimalRoute);

 //   void handleMainWindowEvents(sf::Event &event, sf::RenderWindow &window, std::vector<Paczka> &paczki, Magazyn &magazyn, Kurier &kurier, Mapa &mapa,
 //                               std::vector<std::string> &routes, bool &showMap, UIElements &uiElements, std::vector<std::string> &inputBuffers, int &step);

    void drawMainWindow(sf::RenderWindow &window, sf::Font &font, std::vector<Paczka> &paczki, std::vector<std::string> &routes, UIElements &uiElements);

    std::pair<sf::RectangleShape, sf::Text> createButton(const sf::Vector2f &position, const std::string &text, const sf::Color &color, sf::Font &font);

    void addPackageDetails(sf::Font &font, std::vector<Paczka> &paczki, float x, float y);

private:
    double calculateDistance(double x1, double y1, double x2, double y2);
    std::vector<std::string> inputBuffers{5, ""}; // 5 fields: ID, address, weight, x, y
    std::vector<Paczka> currentRoute;
    int step = 0;
    bool selectingFromMap = false; // Flaga wskazująca, czy wybieramy punkt z mapy
};

#endif // DRAW_H
