#pragma once
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <fstream>
#include <sstream>

#include "Player.h"
#include "Tilebag.h"
#include "TileCodes.h"
#include "Board.h"


#define SIZE_ROW    26
#define SIZE_COL    26
#define CHECK_ROW   105
#define CHECK_COL   205
#define PLAYER1     0
#define PLAYER2     1

class GameEngine {
       
public:
    GameEngine(std::string player1Name, std::string player2Name);
    GameEngine(Player* player1, Player* player2, Board* board, Tilebag* bag);
    ~GameEngine();
    bool isLegalPos(std::string tile, std::string location);
    void loadGame(std::string filename);
    void saveGame(std::string filename);
    void placeTile(Player& player, Tile* tile, std::string pos);
    void place(Player& player, Tile* tile, std::string pos);
    void removeTile(std::string pos);
    void replaceTileOnHand();
    Board* getBoard();
    Player* getPlayer(int player);
    Player* getCurrentPlayer();
    Player* getOtherPlayer();
    int getOtherPlayerInt();
    int getCurrentPlayerInt();
    void setCurrentPlayerInt(int playerInt);
    void setOtherPlayerInt(int playerInt);
    void setCurrentPlayer(int nextPlayer);
    bool isGameEnd() const;
    void printEndResult();
    
private:
    int x, y;
    void convertStringPosToInt(std::string pos);
    Tilebag *tilebag = new Tilebag();
    Board *board = new Board();
    Player *players[NO_PLAYERS];
    int currentPlayer;
    int otherPlayer;
    bool checkDuplicate(char colour, int shape, int row, int col, int rowOrCol);
    bool isTileCodeValid(std::string tileCode);
    bool isTileCodeValid(Colour tileColour, Shape tileShape);
    bool updateScore(Player& player, Tile* tile, const int row, const int col);
    bool boardEmpty();
};


#endif // ASSIGN2_ENGINE_H

