#include <iostream>

#include "Coordinate.h"



Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Coordinate::setRow(int x)
{
    this->x = x;
}

void Coordinate::setCol(int y)
{
    this->y = y;
}

int Coordinate::getRow()
{
    return x;
}

int Coordinate::getCol()
{
    return y;
}

