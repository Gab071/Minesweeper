#include "MinesweeperBoard.h"
#include <cassert>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "MSSFMLController.h"
#include "MSSFMLView.h"

void test_1(MinesweeperBoard & plansza);

int main()
{
    // sf::Style::Titlebar | sf::Style::Close
    sf::RenderWindow menuWindow(sf::VideoMode({800, 600}), "Minesweeper");
    Menu menu;
    menu.controlMenu(menuWindow);

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper");
    MinesweeperBoard board(10, 10, menu.getGameMode());
    board.debug_display();
    MSSFMLView view (board);  // przekazujemy przez referencję planszę jako argument konstruktora
    MSSFMLController ctrl (board, view);
    ctrl.play(window);

    board.debug_display();

    return 0;
}

//Aserty są dla planszy 5*6 oraz trybu debug
void test_1(MinesweeperBoard & plansza)
{
    assert(plansza.getBoardHeight() == 5);
    assert(plansza.getBoardWidth() == 6);
    assert(plansza.getGameState() == 0);
    assert(plansza.getFieldInfo(0, 0) == '_');

    assert(plansza.isRevealed(1,1) == false);
    plansza.revealField(1,1);
    assert(plansza.isRevealed(1,1) == true);
    assert(plansza.getFieldInfo(1,1) == '5');
    plansza.toggleFlag(0,0);
    assert(plansza.hasFlag(0,0) == true);
    assert(plansza.countMines(0,0) == -1);

    plansza.revealField(2,2);
    assert(plansza.getGameState() == 2);
    plansza.revealField(3,3);
}