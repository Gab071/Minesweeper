//
// Created by kamin on 29.04.2025.
//

#ifndef MSSFMLVIEW_H
#define MSSFMLVIEW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "MinesweeperBoard.h"


class MSSFMLView {
    MinesweeperBoard& board;
    int tileSize = 64;
    float scale = 1.0f;

    // Tu po prostu kalkulujemy jaki rozmiar będzie posiadała nasza nowa plansza
    int boardWidth = board.getBoardWidth();
    int boardHeight = board.getBoardHeight();
    int pixelWidth = boardWidth * tileSize;
    int pixelHeight = boardHeight * tileSize + tileSize;

    std::map<char, sf::Texture> textures;
    std::map<char, sf::Sprite> sprites;

    sf::Texture hiddenTexture;
    sf::Sprite hiddenSprite;

    /// Funkcja odpowiedzialna za załadowanie grafik (teraz jest w Konstruktorze)
    void loadTextures();

    /// Funkcja odpowiedzialna za stworzenie sprites (grafika dla sfml)
    void setupSprites();

    /// Funkcja, która przeskalowuje planszę, gdy okno zmienia rozmiar
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    /// \param offsetX wyśrodkowuje planszę po width
    /// \param offsetY wyśrodkowuje planszę po lenght
    void scaleBoard(sf::RenderWindow& window, float &offsetX, float &offsetY);

    /// Dwie funkcje, które mogą się przydać
    void createRectangle(sf::RectangleShape & rectangle, const float& offsetX, sf::RenderWindow& window);
    void createCircle(sf::CircleShape & circle, sf::RenderWindow& window);
public:
    /// Konstruktor
   explicit  MSSFMLView(MinesweeperBoard& board);

    void draw(sf::RenderWindow& window);

    /// Funkcja jest odpowiedzialna za wyświetlanie komunikaty po zakończeniu gry
    void drawGameOver(sf::RenderWindow & window);

    /// Funkcja pobiera titleSize, aby oddać do klasy MSSFMLController
    int getTileSize() const;
};

#endif //MSSFMLVIEW_H
