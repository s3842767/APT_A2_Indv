
#include "Tilebag.h"

Tilebag::Tilebag(){

    char colours[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
    int shapes[] = {1, 2, 3, 4, 5, 6};

    this->allTiles = new LinkedList();
    for (int i = 0; i < TILE_DUPLICATION; i++){
        for (int index = 0; index < COLOURS_SIZE; index++){
            for (int counter = 0; counter< SHAPES_SIZE; counter++){
                Tile *tile = new Tile(colours[index], shapes[counter]);
                allTiles->addFront(tile);
            }
        }
    }

}

Tilebag::~Tilebag(){
    allTiles->clear();
}

Tile* Tilebag::getTile(){
    Tile* tile =  allTiles->get(0);
    allTiles->removeFront();
    return tile;

}

void Tilebag::shuffle() {

    std::vector<Tile*> shuffleTiles;

    for (unsigned int i = 0; i < allTiles->getSize(); i++){
        shuffleTiles.push_back(allTiles->get(i));
    }

    std::random_device rd;
    std::shuffle(std::begin(shuffleTiles), std::end(shuffleTiles), rd);

    allTiles->clear();

    for (unsigned int i =0; i < shuffleTiles.size(); i++){
        allTiles->addFront(shuffleTiles[i]);
    }

}

Tile* Tilebag::take() {
    Tile* t = new Tile(this->allTiles->get(0)->getColour(), this->allTiles->get(0)->getShape());
    this->allTiles->removeFront();
    return t;

}

void Tilebag::add(Tile* tile) {
    this->allTiles->addBack(tile);
}

bool Tilebag::isEmpty(){
    bool isEmpty = false;
    if (allTiles->getSize()<1){
        isEmpty = true;
    }
    return isEmpty;
}

void Tilebag::clear(){
    delete this->allTiles;
    this->allTiles = new LinkedList();
}



