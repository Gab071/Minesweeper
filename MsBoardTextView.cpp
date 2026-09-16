//
// Created by c on 4/24/25.
//
#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

MsBoardTextView::MsBoardTextView(MinesweeperBoard & board) : board{board}
{

}

void MsBoardTextView::display() const
{
    int width = board.getBoardWidth();
    int height  = board.getBoardHeight();

    for(int ncol = 0; ncol < width; ncol++)
    {
        cout << std::setw(5) << ncol;
    }
    cout << endl;

    for(int nrow = 0; nrow < height; nrow++)
    {
        cout << nrow << " ";
        for(int ncol = 0; ncol < width; ncol++)
        {
            if(ncol == 0)
                cout << std::setw(3) << board.getFieldInfo(nrow, ncol);
            else
            cout << std::setw(5) << board.getFieldInfo(nrow, ncol);
        }
        cout << endl;
    }
}