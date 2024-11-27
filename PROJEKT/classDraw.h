#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Paczka;
class Magazyn;
class Kurier;
class Mapa;


class classDraw {
public:
    // Konstruktor domyślny
    classDraw();

    // Funkcja do wprowadzania współrzędnych magazynu
    void MagazynInput(sf::Font& font, std::vector<std::string>& magazynInputBuffers, int& magazynStep, double& magazynX, double& magazynY);

    void MainWindow(
        sf::RenderWindow& window,
        sf::Font& font,
        std::vector<Paczka>& paczki,
        Magazyn& magazyn,
        Kurier& kurier,
        Mapa& mapa
    );
};

#endif // DRAW_H
