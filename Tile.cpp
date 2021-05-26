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

void Tile::setTileColour()
{
    tileColour = TRED;
    if(colour == 'R')
    {
        tileColour == TRED;
    }
    if(colour == 'O')
    {
        tileColour == TORANGE;
    }
    if(colour == 'Y')
    {
        tileColour == TYELLOW;
    }
    if(colour == 'B')
    {
        tileColour == TBLUE;
    }
    if(colour == 'P')
    {
        tileColour == TPURPLE;
    }

}

std::string Tile::getTileColour()
{
    return tileColour;
}



