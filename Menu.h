//
// Created by kamin on 26.05.2025.
//

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

enum GameMode  { DEBUG, EASY, NORMAL, HARD };

class Menu {

    GameMode choose_mode;
    bool exitMenu;
public:
    Menu();
    void controlMenu(sf::RenderWindow & menuWindow);
    bool keyClick(sf::Event & event);
    void drawMenu(sf::RenderWindow & menuWindow);

    GameMode getGameMode() const;
};


#endif //MENU_H
