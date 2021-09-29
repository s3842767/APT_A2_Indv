#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <iostream>
#include "Types.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;


class Tile {
public:
   Tile(Colour colour, Shape shape);
   char getColour();
   void setColour(Colour colour);
   
   int getShape();
   void setShape(Shape shape);

   void setTileColour(char c);
   std::string getTileColour();

private:
   Colour colour;
   Shape  shape;
   std::string tileColour;
};


#endif // ASSIGN2_TILE_H

