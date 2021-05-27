#include    "Player.h"

#include <string>
#include <sstream>

Player::Player(std::string name){
    this->name = name;
    this->score= 0;
    this->hand = nullptr;
}

Player::~Player(){
    if(this->hand != nullptr)
        delete this->hand;
}

bool Player::checkTileOnHand(std::string tileCode)
{
    bool exist = false;

    // Since tile code should be <colour><shape>, then only 2 characters are expected
    if(tileCode.length() == 2)
    {
        for (unsigned int i = 0; i < hand->getSize(); i++){
            if (hand->get(i)->getColour() == tileCode.at(FIRST_CHAR) && std::to_string(hand->get(i)->getShape()).compare(std::to_string(tileCode.at(1)))){
                exist = true;
            }
        }
    }
    return exist;
}

Tile* Player::getNew(std::string tileString)
{
    int shape;
    std::stringstream lc;
    lc << tileString[1];
    lc >> shape;
    char colour = tileString.at(0);

    Tile* tile = new Tile(colour, shape);
    return tile;
}

Tile* Player::getTile(std::string tileString)
{
    
    int sh;
    std::stringstream lc;
    lc << tileString[1];
    lc >> sh;
    char cl = tileString.at(0);
    
    Tile* t = nullptr;
    for (unsigned int i =0; i < hand->getSize(); i++){
        if (hand->get(i)->getColour() == cl && hand->get(i)->getShape() == sh){
            t = hand->get(i);
            hand->remove(i);
            return t;
        }
    }
    std::cout<< "PLAYER::GET_TILE() - TILE NOT FOUND"<<std::endl;
    return t;
}

std::string Player::getName() {
    return this->name;
}

void Player::setName(std::string name) {
    this->name = name;
}

int Player::getScore() {
    return this->score;
}

void Player::setScore(int score) {
    this->score = score;
}

LinkedList* Player::getHand() {
    return this->hand;
}

void Player::setHand(LinkedList* linkedList) {
    this->hand = linkedList;
}

void Player::addTileToHand(Tile* tile){
    hand->addBack(tile);
}

std::string Player::printTilesOnHand(){
    std::string tilesOnHand = "";
    for (unsigned int index = 0; index < hand->getSize(); index++){
        if (hand->get(index)!= nullptr){
            hand->get(index)->setTileColour(hand->get(index)->getColour());
            tilesOnHand += hand->get(index)->getTileColour() + hand->get(index)->getColour() + std::to_string(hand->get(index)->getShape()) + " " + TWHITE;
        }
    }
    return tilesOnHand;
}