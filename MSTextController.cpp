//
// Created by c on 4/24/25.
//

#include "MSTextController.h"

MSTextController::MSTextController(MinesweeperBoard & board, MsBoardTextView & view) : board(board), view(view)
{

}

void MSTextController::play() const
{
    char command;
    int row, col;

    while(board.getGameState() == RUNNING)
    {
        view.display();
        cout << "If you want to reveal field type: r row col" << endl;
        cout << "If you want to place or remove a flag type f row col" << endl;

        std::cin >> command >> row >> col;

        if(command == 'r')
            board.revealField(row, col);

        else if(command == 'f')
            board.toggleFlag(row, col);

        else
            cout << "Wrong command" << endl;


        if(board.getGameState() != RUNNING)
        {
            view.display(); // Drugi raz trzeba, aby wyświetlić po zakończeniu gry
            if (board.getGameState() == FINISHED_WIN)
                cout << "!!!Congratulations, you won!!!" << endl;
            else {
                cout << "You lost" << endl;
            }
            break;
        }
    }
}