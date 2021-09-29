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

    public:
        // Creates the initial state of the board
        Board();

        // Prints the Board
        void printBoard();

        bool addTileToBoard(Coordinate* coords, Tile* tile);
        bool replaceTileOnBoard(Coordinate* coords, Tile* tile);
        bool removeTileOnBoard(Coordinate* coords);
        Tile* getTileAtPos(int row, int col);
    private:
        std::vector<std::vector<Tile*> > board;
};

#endif // ASSIGN2_BOARD_H