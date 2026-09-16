#ifndef SAPER_MSBOARDTEXTVIEW_H
#define SAPER_MSBOARDTEXTVIEW_H

#include "MinesweeperBoard.h"

class MsBoardTextView {
    MinesweeperBoard & board;
public:
   explicit MsBoardTextView (MinesweeperBoard & board);
    void display() const;
};


#endif //SAPER_MSBOARDTEXTVIEW_H
