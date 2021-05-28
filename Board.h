#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include <string>
#include "Player.h"
#include "Tile.h"
#include "Coordinate.h"

#define GRID_LENGTH 26

class Board
{
    std::vector<std::vector<Tile*> > board;

    // Column labels to be printed
    std::string colLabels[6] = {"A ", "B ", "C ", "D ", "E ", "F "};
    //int colLabelCount;

    public:
        // Creates the initial state of the board
        Board();

        // Prints the Board
        void printBoard();

        bool addTileToBoard(Coordinate* coords, Tile* tile);
        bool replaceTileOnBoard(Coordinate* coords, Tile* tile);
        bool removeTileOnBoard(Coordinate* coords);
        Tile* getTileAtPos(int row, int col);
};

#endif // ASSIGN2_BOARD_H