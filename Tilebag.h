
#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "Tile.h"
#include "LinkedList.h"
#include "Types.h"

#include <stdlib.h>    
#include <time.h> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


class Tilebag : public LinkedList{
public:
    Tilebag();
    virtual ~Tilebag();
    Tile* take();
    void add(Tile* tile);
    bool isEmpty();
    void addTile(Tile *tile);
    Tile* getTile();
    void shuffle();
    void clear();

private:
    int numberOfTiles;
    LinkedList* allTiles;
};

#endif // ASSIGN2_TILEBAG_H
