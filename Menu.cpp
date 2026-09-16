
#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Menu::Menu() : choose_mode(EASY), exitMenu(false)
{

}

void Menu::controlMenu(sf::RenderWindow & menuWindow)
{
    menuWindow.setVerticalSyncEnabled(false);
    menuWindow.setFramerateLimit(60);

    while (menuWindow.isOpen() and !exitMenu)
    {
        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                menuWindow.close();
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                menuWindow.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if(keyClick(event))
                    exitMenu = true;
            }
        }
        menuWindow.clear(sf::Color::Black);
        drawMenu(menuWindow);
        menuWindow.display();
    }
    menuWindow.close();
}

bool Menu::keyClick(sf::Event &event)
{
    if(event.key.code == sf::Keyboard::Num1)
    {
        choose_mode = EASY;
        return true;
    }

    if(event.key.code == sf::Keyboard::Num2)
    {
        choose_mode = NORMAL;
        return true;
    }

    if(event.key.code == sf::Keyboard::Num3)
    {
        choose_mode = HARD;
        return true;
    }
    return false;
}

void Menu::drawMenu(sf::RenderWindow & menuWindow)
{
    sf::Vector2u size = menuWindow.getSize();

    sf::Font font;
    if (!font.loadFromFile("PressStart2P-Regular.ttf"))
    {
        std::cerr << "Could not load font\n";
    }
    sf::Text diff;
    diff.setFont(font);

    diff.setString("Choose a difficulty:");

    diff.setCharacterSize(50);
    diff.setFillColor(sf::Color::Blue);
    diff.setStyle(sf::Text::Bold);
    sf::FloatRect diffBounds = diff.getLocalBounds();
    diff.setOrigin(diffBounds.left + diffBounds.width / 2.0f, 0);
    diff.setPosition(size.x / 2.0f, size.y / 30.0f);
    menuWindow.draw(diff);

    sf::Text easy;
    easy.setFont(font);
    easy.setString("Easy: press 1");
    easy.setCharacterSize(50);
    easy.setFillColor(sf::Color::Green);
    easy.setStyle(sf::Text::Bold);
    sf::FloatRect easyBounds = easy.getLocalBounds();
    easy.setOrigin(easyBounds.left + easyBounds.width / 2.0f, easyBounds.top + easyBounds.height / 2.0f);
    easy.setPosition(size.x / 2.0f, size.y / 4.0f);
    menuWindow.draw(easy);

    sf::Text normal;
    normal.setFont(font);
    normal.setString("Normal: press 2");
    normal.setCharacterSize(50);
    normal.setFillColor(sf::Color::Yellow);
    normal.setStyle(sf::Text::Bold);
    sf::FloatRect normalBounds = normal.getLocalBounds();
    normal.setOrigin(normalBounds.left + normalBounds.width / 2.0f, normalBounds.top + normalBounds.height / 2.0f);
    normal.setPosition(size.x / 2.0f, size.y / 2.5f);
    menuWindow.draw(normal);

    sf::Text hard;
    hard.setFont(font);
    hard.setString("Hard: press 3");
    hard.setCharacterSize(50);
    hard.setFillColor(sf::Color::Red);
    hard.setStyle(sf::Text::Bold);
    sf::FloatRect hardBounds = hard.getLocalBounds();
    hard.setOrigin(hardBounds.left + hardBounds.width / 2.0f, hardBounds.top + hardBounds.height / 2.0f);
    hard.setPosition(size.x / 2.0f, size.y / 1.75f);
    menuWindow.draw(hard);

}

GameMode Menu::getGameMode() const
{
    return choose_mode;
}


