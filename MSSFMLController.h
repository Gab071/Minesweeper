//
// Created by c on 5/8/25.
//

#ifndef SAPER_MSSFMLCONTROLLER_H
#define SAPER_MSSFMLCONTROLLER_H

#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include <SFML/Graphics.hpp>

class MSSFMLController {

    MinesweeperBoard & board;
    MSSFMLView & view;
    int tileSize;

    bool Triggered;
    bool is_gameOver;

    /// Funkcja obsługuje kliknięcie myszy
    /// \param event odpowiedzialny za obsługę zdarzeń (Closed, Resized, Mouseclick)
    void mouseClick(sf::RenderWindow & window, sf::Event & event);

    /// Funkcja odpowiedzialna za rozpoczęcie zegarka n sekundowego po zanończeniu rozgrywki
    /// \param clock ten zegareczek, który odlicza n sekund
    void clockStart(sf::Clock & clock);

    /// Funkcja obsługuje zdarzenia (Closed, Resized, Mouseclick)
    /// \param event odpowiedzialny za obsługę zdarzeń (Closed, Resize, Mouseclick)
    void Events(sf::RenderWindow & window, sf::Event & event);


public:
    /// Konstruktor
    MSSFMLController(MinesweeperBoard & board, MSSFMLView & view);

    /// Funckja obsługująca rozgrywkę
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    void play(sf::RenderWindow & window);

};


#endif //SAPER_MSSFMLCONTROLLER_H
