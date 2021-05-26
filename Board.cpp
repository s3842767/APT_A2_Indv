#include <iostream>

#include "Board.h"
#include "Coordinate.h"

Board::Board()
{
    for(int i = 0; i < GRID_LENGTH; ++i){
        std::vector<Tile*> row;
        board.push_back(row);
        for(int n = 0; n < GRID_LENGTH; ++n)
        {
            board[i].push_back(nullptr);
        }
    }
}

void Board::printBoard()
{
    std::string colLabels[] = {"A ", "B ", "C ", "D ", "E ", "F ",
     "G ", "H ", "I ", "J ", "K ", "L ", "M ", "N ", "O ", "P ",
      "Q ", "R ", "S ", "T ", "U ", "V ","W ", "X ", "Y ","Z "};
   int colLabelCount = 0;

   std::cout << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" << std::endl;
   std::cout << "  ------------------------------------------------------------------------------" << std::endl;
    for(unsigned int x = 0; x < board.size(); x++)
    {
        // Column labels
        std::cout << colLabels[colLabelCount];
        colLabelCount += 1;
        for(unsigned int y = 0; y < board[x].size(); y++)
        {
            if(board[x][y] == nullptr)
            {
                std::cout << "|" << "  ";
            }
            if(board[x][y] != nullptr)
            {
                board[x][y]->setTileColour(board[x][y]->getColour());
                std::cout << "|" << board[x][y]->getTileColour() << board[x][y]->getColour() << board[x][y]->getShape() << TWHITE;
            }
        }
        std::cout << "|" << std::endl;
    }
}

bool Board::addTileToBoard(Coordinate* coords, Tile* tile)
{
    if(board[coords->getRow()][coords->getCol()] == nullptr)
    {
        board[coords->getRow()][coords->getCol()] = tile;
        return true;
    }
    return false;
}

bool Board::replaceTileOnBoard(Coordinate* coords, Tile* tile)
{
    if(board[coords->getRow()][coords->getCol()] != tile)
    {
        board[coords->getRow()][coords->getCol()] = tile;
        return true;
    }
    return false;
}

bool Board::removeTileOnBoard(Coordinate* coords)
{
    if(board[coords->getRow()][coords->getCol()] != nullptr)
    {
        board[coords->getRow()][coords->getCol()] = nullptr;
        return true;
    }
    return false;
}

Tile* Board::getTileAtPos(char row, int col){
   return board[row][col];
}