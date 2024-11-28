#ifndef HANDLING_EVENTS_H
#define HANDLING_EVENTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "classPaczka.h"
#include "classMagazyn.h"
#include "classKurier.h"
#include "classMapa.h"
#include "classDraw.h"

class Paczka;
class Magazyn;
class Kurier;
class Mapa;

// struct UIElements
// {
//     sf::Text inputText;
//     std::vector<sf::RectangleShape> inputFields;       // Pola wejściowe
//     std::vector<sf::Text> inputTexts;                  // Teksty wprowadzane
//     std::vector<sf::Text> inputLabels;                 // Etykiety dla pól wejściowych
//     std::map<std::string, sf::RectangleShape> buttons; // Przycisk mapowany na nazwy
//     std::map<std::string, sf::Text> buttonTexts;       // Teksty na przyciskach
// };

class classHandlingEvents
{
public:
    // Konstruktor domyślny
    classHandlingEvents();

    void handleTextInput(sf::Event &event, std::vector<std::string> &inputBuffers, int &step, UIElements &uiElements);

    void handleMouseClick(sf::Event &event, std::vector<Paczka> &paczki, Magazyn &magazyn, Kurier &kurier, Mapa &mapa, std::vector<std::string> &routes, bool &showMap, UIElements &uiElements);

    void handleMainWindowEvents(sf::Event &event, sf::RenderWindow &window, std::vector<Paczka> &paczki, Magazyn &magazyn, Kurier &kurier, Mapa &mapa,
                                std::vector<std::string> &routes, bool &showMap, UIElements &uiElements, std::vector<std::string> &inputBuffers, int &step);

private:
    double calculateDistance(double x1, double y1, double x2, double y2);
    std::vector<std::string> inputBuffers{5, ""}; // 5 fields: ID, address, weight, x, y
    std::vector<Paczka> currentRoute;
    int step = 0;
    bool selectingFromMap = false; // Flaga wskazująca, czy wybieramy punkt z mapy
};

#endif // HANDLING_EVENTS_H
