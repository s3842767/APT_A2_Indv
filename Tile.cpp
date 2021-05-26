#include "Tile.h"
#include "Types.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

char Tile::getColour(){
    return this->colour;
}

int Tile::getShape(){
    return this->shape;
}

void Tile::setColour(Colour colour){
    this->colour = colour;
}

void Tile::setShape(Shape shape){
    this->shape = shape;
}

void Tile::setTileColour(char c)
{
    tileColour = TRED;
    if(c == RED)
    {
        tileColour = TRED;
    }
    if(c == ORANGE)
    {
        tileColour = TORANGE;
    }
    if(c == YELLOW)
    {
        tileColour = TYELLOW;
    }
    if(c == BLUE)
    {
        tileColour = TBLUE;
    }
    if(c == PURPLE)
    {
        tileColour = TPURPLE;
    }

}

std::string Tile::getTileColour()
{
    return tileColour;
}



