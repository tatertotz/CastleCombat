#include "Cell.h"

Cell::~Cell()
{
    //dtor
}

Cell::Cell(int x, int y, string type, string iconFile)
{
    this->x=x;
    this->y=y;
    this->type=type;
    this->iconFile=iconFile;
}

void Cell::run()
{

}


int Cell::getX()
{
    return this->x;
}

int Cell::getY()
{
    return this->y;
}

string Cell::getIconFile()
{
    return this->iconFile;
}
