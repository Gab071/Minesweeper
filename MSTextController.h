//
// Created by c on 4/24/25.
//

#ifndef SAPER_MSTEXTCONTROLLER_H
#define SAPER_MSTEXTCONTROLLER_H

#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

class MSTextController {
MinesweeperBoard & board;
MsBoardTextView & view;

public:
    MSTextController (MinesweeperBoard & board, MsBoardTextView & view);
    void play() const;
};


#endif //SAPER_MSTEXTCONTROLLER_H
