#pragma once

#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Tile.h"
#include "Types.h"

class Player{

public: 

    Player(std::string name);
    ~Player();

    std::string getName();
    void setName(std::string name);

    int getScore();
    void setScore(int score);
    void addPoint();

    LinkedList* getHand();
    void setHand(LinkedList* LinkedList);

    bool checkTileOnHand(std::string tileCode);

    Tile* getNew(std::string tileString);

    std::string printTilesOnHand();

    void addTileToHand(Tile* tile);

    Tile* getTile(std::string tileString);
        

private:
    std::string name;
    int score;
    LinkedList* hand;
};

#endif // ASSIGN2_PLAYER_H
