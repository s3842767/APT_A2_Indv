#ifndef ASSIGN2_COORDINATE_H
#define ASSIGN2_COORDINATE_H

class Coordinate
{
    int x;
    int y;

    public:

        Coordinate(int x, int y);

        void setRow(int x);
        void setCol(int y);
        int getRow();
        int getCol();
};

#endif // ASSIGN2_COORDINATE_H