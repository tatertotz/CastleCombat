#include "Cell.h"


Cell::Cell()
{

}

Cell::Cell(wxPoint point, string type, string name, string iconFile, string healthFile)
{
    this->point=point;
    this->type=type;
    this->name=name;
    this->iconFile=iconFile;
    this->healthFile=healthFile;
    ran=false;
}

Cell::~Cell()
{
}
    //dtor

void Cell::run()
{

}

int Cell::getX()
{
    return point.x;
}

int Cell::getY()
{
    return point.y;
}

void Cell::setCoordinates(wxPoint point)
{
    this->point=point;
}





