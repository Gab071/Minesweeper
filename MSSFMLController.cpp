
#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard & board, MSSFMLView & view) :
board{board}, view{view}, Triggered(false), is_gameOver(false)
{
    tileSize = view.getTileSize();
}

void MSSFMLController::play(sf::RenderWindow & window)
{
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Events(window, event);
        }

        clockStart(clock);

        window.clear();

        if(!is_gameOver)
        view.draw(window);

        else
            view.drawGameOver(window);

        window.display();
    }
}

void MSSFMLController::mouseClick(sf::RenderWindow & window, sf::Event & event)
{
    tileSize = view.getTileSize();
    sf::Vector2u winSize = window.getSize();
    int height = board.getBoardHeight();
    int width = board.getBoardWidth();
    int tileY = (winSize.y - height * tileSize) / 2;
    // int tileY = (winSize.y - height * tileSize + tileSize) / 2;
    int tileX = (winSize.x - width * tileSize) / 2;
    int wiersz = (event.mouseButton.y - tileY) / tileSize;
    int kolumna = (event.mouseButton.x - tileX) / tileSize;

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        board.revealField(wiersz, kolumna);
    }
    if(event.mouseButton.button == sf::Mouse::Right)
    {
        board.toggleFlag(wiersz, kolumna);
    }
}

void MSSFMLController::clockStart(sf::Clock & clock)
{
    if (board.getGameState() != RUNNING && !Triggered)
    {
        clock.restart();
        Triggered = true;
    }

    if (Triggered && clock.getElapsedTime().asSeconds() >= 3.f)
    {
        is_gameOver = true;
    }
}

void MSSFMLController::Events(sf::RenderWindow & window, sf::Event & event)
{
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
    if (event.type == sf::Event::MouseButtonPressed && !is_gameOver)
    {
        mouseClick(window, event);
    }
}





