#ifndef MINESBOARD_H__
#define MINESBOARD_H__

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include "Array2D.h"
#include "Menu.h"


using std::cout;
using std::endl;

//enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
    // this is just a hint; you are free to implement PRIVATE section in any way you want
    Array2D<Field> board = Array2D<Field>(0,0);

    int width;
    int height;
    GameMode mode;
    GameState state;
    bool game_s;

    /// Funkcja czyści planszę (zmienia wszystkie wartości na fałsz)
    void clearBoard();

    /// Funkcja dla potrzeb debugowania stwarza nową wcześniej zdefiniowaną planszę
    void debugBoard();

    /// Funkcja wykłada miny na planszy używając funkcji guessMines oraz mCount do pobrania min od odpowiedniej trudności
    /// \param ratio: procent min w trudności
    void placeMines(float ratio);

    /// Funkcja wylosowuje miny
    /// \param prob: ilość min
    void guessMines(const int prob);

    /// Funkcja liczy ilość min dla odpowiedniego poziomu trudności
    /// \param ratio: procent min w trudności
    /// \return : ilość min w poziomie trudności
    int mCount(const float ratio) const;

    /// Funkcja sprawdza, czy row oraz col nie wychodzą za granicę planszy
    /// \param row
    /// \param col
    /// \return
    bool outBoard(int row, int col) const;

    /// Funkcja otwiera naokoło pola inne pola, jeżeli pole na około nie posiada min
    /// \param row
    /// \param col
    void revealEmptyFields(const int row, const int col);

    /// Funkcja zwraca prawdę, jeżeli w polu pod row, col jes mina
    bool hasMine(const int row, const int col) const;

    /// Funkcja sprawdza, czy gra się skończyła (dla przypadku Finished win)
    void gameOver();

public:
    // generate "default" board (according to earlier instructions)
    MinesweeperBoard();

    // generate a width*height sized board with the number of mines that depend on GameMode:
    // - EASY   - 10% of game fields with mines (random)
    // - NORMAL - 20% of game fields with mines (random)
    // - HARD   - 30% of game fields with mines (random)
    // - DEBUG  - predefined mine layout (read at the end of file)
    //
    // NOTE: You may assume, that width and height are not larger than 100
    // HINT: It is OK to allocate 100x100 board and only use part of it
    MinesweeperBoard(int width, int height, GameMode mode);

    // simple getters - return appropriate values (passed to or calculated in constructor)
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;

    // count mines around (row,col) position
    // if the field at (row,col) was not revealed - return -1
    // if either row or col is outside board      - return -1
    // otherwise - return mine count around this field
    // Examples for DEBUG layout on 10x10 board (assuming the field is already revealed)
    // - countMines(1,0) should return 4
    // - countMines(2,9) should return 0
    // - countMines(2,1) should return 3
    // - countMines(6,7) should return 2
    int countMines(int row, int col) const;


    // return true if the field at (row,col) position was marked with flag
    // return false if any of the following is true:
    // - row or col is outside board
    // - there is no flag on the field
    // - field was already revealed
    bool hasFlag(int row, int col) const;

    // if the field at (row,col) was not revealed - change flag status for this field
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    void toggleFlag(int row, int col);

    // try to reveal the field at (row,col)
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    // - there is a flag on the field
    //
    // If the field was not revealed and there is no mine on it - reveal it
    // If the field was not revealed and there is a mine on it:
    // - if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
    // - reveal it and finish game
    void revealField(int row, int col);

    // return true if the field was revealed
    // return false if the field is not revealed or if it is outside the board
    bool isRevealed(int row, int col) const;

    // return current game state:
    // - FINISHED_LOSS - if the player revealed field with mine
    // - FINISHED_WIN  - if the player won the game (all unrevealed fields have mines)
    // - RUNNING       - if the game is not yet finished
    GameState getGameState() const;

    // convenience function - returns useful information about field in one function call
    // if row or col is outside board                         - return '#' character
    // if the field is not revealed and has a flag            - return 'F' character
    // if the field is not revealed and does not have a flag  - return '_' (underscore) character
    // if the field is revealed and has mine                  - return 'x' character
    // if the field is revealed and has 0 mines around        - return ' ' (space) character
    // if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
    char getFieldInfo(int row, int col) const;

    void debug_display() const;

};

#endif