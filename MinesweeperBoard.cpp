#include "MinesweeperBoard.h"

void MinesweeperBoard::clearBoard()
{
    for (int nrow = 0; nrow < height; nrow++)
    {
        for (int ncol = 0; ncol < width; ncol++)
        {
            board[nrow][ncol].hasFlag = false;
            board[nrow][ncol].hasMine = false;
            board[nrow][ncol].isRevealed = false;
        }
    }
}

MinesweeperBoard::MinesweeperBoard()
{
    // height = 7;
    // width = 5;
    // game_s = true;
    // board.resize(height, width);
    // clearBoard();
    //
    // board[0][0].hasMine = true;
    // board[1][1].isRevealed = true;
    // board[0][2].hasMine = true;
    // board[0][2].hasFlag = true;
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode)
    : width(width), height(height), mode(mode), state(RUNNING), game_s(true)
{

    srand(time(nullptr));
    if (height > 100 || width > 100)
        exit(0);

    if (height < 0 || width < 0)
        exit(0);

    if (height == 1 && width == 1)
        exit(0);

    board.resize(height, width);
    clearBoard();

    switch (mode)
    {
    case DEBUG:
        debugBoard();
        break;

    case EASY:
        placeMines(0.1);
        break;

    case NORMAL:
        placeMines(0.2);
        break;

    case HARD:
        placeMines(0.3);
        break;

    default:
        cout << "Invalid mode" << endl;
        exit(0);
    }
}

void MinesweeperBoard::debug_display() const
{
    for (int ncol = 0; ncol < width; ncol++)
    {
        cout << std::setw(5) << ncol;
    }
    cout << endl;

    for (int nrow = 0; nrow < height; nrow++)
    {
        cout << nrow << " ";
        for (int ncol = 0; ncol < width; ncol++)
        {
            cout << "[" << (board[nrow][ncol].hasMine ? "M" : ".");
            cout << (board[nrow][ncol].isRevealed ? "o" : ".");
            cout << (board[nrow][ncol].hasFlag ? "f" : ".");
            cout << "]";
        }
        cout << endl;
    }
}

void MinesweeperBoard::debugBoard()
{
    for (int ncol = 0; ncol < width; ncol++)
    {
        board[0][ncol].hasMine = true;
    }
    for (int n = 0; n < fmin(height, width); n++)
    {
        board[n][n].hasMine = true;
    }
    for (int nrow = 0; nrow < height; nrow++)
    {
        if (nrow % 2 == 0)
        {
            board[nrow][0].hasMine = true;
        }
    }
}

void MinesweeperBoard::placeMines(const float ratio)
{
    const int prob = mCount(ratio);

    guessMines(prob);
}

int MinesweeperBoard::mCount(const float ratio) const
{
    const double round = static_cast<float>(height * width) * ratio;
    const int counter = ceil(round);
    return counter;
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

// To można zmienić, lepiej byłoby od razu pobierać prob (czyli już policzoną ilość min)
int MinesweeperBoard::getMineCount() const
{
    int count = 0;
    for (int nrow = 0; nrow < height; nrow++)
    {
        for (int ncol = 0; ncol < width; ncol++)
        {
            if (board[nrow][ncol].hasMine)
                count++;
        }
    }
    return count;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    if (outBoard(row, col))
        return -1;

    // To można zakomentować przy testowaniu, bo field nie będzie revealed
    if (!isRevealed(row, col))
        return -1;

    int count = 0;
    for (int nrow = row - 1; nrow <= row + 1; nrow++)
    {
        for (int ncol = col - 1; ncol <= col + 1; ncol++)
        {
            if (nrow == row && ncol == col)
                continue;

            if (!outBoard(nrow, ncol))
            {
                if (board[nrow][ncol].hasMine)
                    count++;
            }
        }
    }
    return count;
}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (outBoard(row, col))
        return false;

    if (isRevealed(row, col))
        return false;

    if (board[row][col].hasFlag)
        return true;

    return false;
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (outBoard(row, col))
        return false;

    return board[row][col].isRevealed;
}

bool MinesweeperBoard::outBoard(int row, int col) const
{
    if (row < 0 || row >= height)
        return true;

    if (col < 0 || col >= width)
        return true;

    return false;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (outBoard(row, col))
        return;

    if (isRevealed(row, col))
        return;

    if (state != RUNNING)
        return;

    if (hasFlag(row, col))
        board[row][col].hasFlag = false;
    else
        board[row][col].hasFlag = true;
}

void MinesweeperBoard::revealField(int row, int col)
{
    if (isRevealed(row, col))
        return;

    if (outBoard(row, col))
        return;

    if (hasFlag(row, col))
        return;

    if (state == FINISHED_LOSS || state == FINISHED_WIN)
        return;

    if (!board[row][col].hasMine)
    {
        board[row][col].isRevealed = true;
        game_s = false;
    }
    else if (game_s)
    {
        guessMines(1);
        board[row][col].hasMine = false;
        board[row][col].isRevealed = true;
        game_s = false;
    }
    else
    {
        board[row][col].isRevealed = true;
        state = FINISHED_LOSS;
    }

    if (countMines(row, col) == 0)
    {
        revealEmptyFields(row, col);
    }
    gameOver();
}

void MinesweeperBoard::guessMines(const int prob)
{
    int placed = 0;

    while (placed < prob)
    {
        int r = rand() % height;
        int c = rand() % width;
        if (!hasMine(r, c))
        {
            board[r][c].hasMine = true;
            placed++;
        }
    }
}

GameState MinesweeperBoard::getGameState() const
{
    return state;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if (outBoard(row, col))
        return '#';

    if (!isRevealed(row, col) && hasFlag(row, col))
        return 'F';

    if (!isRevealed(row, col) && !hasFlag(row, col))
        return '_';

    if (isRevealed(row, col) && hasMine(row, col))
        return 'x';

    if (isRevealed(row, col) && countMines(row, col) == 0)
        return ' ';

    return static_cast<char>(countMines(row, col)) + '0';
}

void MinesweeperBoard::revealEmptyFields(const int row, const int col)
{
    for (int nrow = row - 1; nrow <= row + 1; nrow++)
    {
        if (hasMine(row, col))
            break;
        for (int ncol = col - 1; ncol <= col + 1; ncol++)
        {
            if (outBoard(nrow, ncol))
                continue;
            if (isRevealed(nrow, ncol))
                continue; // To nie powoduje złego działania funkcji
            if (hasFlag(nrow, ncol))
                continue;
            if (hasMine(nrow, ncol))
                continue;

            board[nrow][ncol].isRevealed = true;

            if (countMines(nrow, ncol) == 0)
            {
                revealEmptyFields(nrow, ncol); // Wywołujemy rekurencyjnie, aby wszystko zostało otworzone
            }
        }
    }
}

bool MinesweeperBoard::hasMine(const int row, const int col) const
{
    if (outBoard(row, col))
        return false;

    return board[row][col].hasMine;
}

void MinesweeperBoard::gameOver()
{
    int correctReveals = 0;
    for (int nrow = 0; nrow < height; nrow++)
    {
        for (int ncol = 0; ncol < width; ncol++)
        {
            if (!hasMine(nrow, ncol) && isRevealed(nrow, ncol))
            {
                correctReveals++;
            }
        }
    }

    const int boardWidth = getBoardWidth();
    const int boardHeight = getBoardHeight();
    const int tiles = boardHeight * boardWidth;
    const int mineCount = getMineCount();
    const int tilesToReveal = tiles - mineCount;

    // std::cout << correctReveals << " " << getMineCount() << " " << tilesToReveal << std::endl;

    if (correctReveals == tilesToReveal)
    {
        state = FINISHED_WIN;
    }
}
