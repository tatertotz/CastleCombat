#include "Castle.h"

Castle::~Castle()
{
    //dtor
}

Castle::Castle(wxFrame* parent)
{
    size = wxSize(8,8);
    cellArr = new Cell*[size.GetWidth()*size.GetHeight()];
    build();
}

void Castle::build()
{
    cellPtr = new Cell**[size.GetWidth()];
    cellArrSize=0;
    for(int y=0;y<size.GetWidth();y++)
    {
        *(cellPtr+y) = new Cell*[size.GetHeight()];
        for(int x =0;x<size.GetHeight();x++)
        {
                Cell* aCell = new Cell(y,x,"Floor","floor32.png");
                cellPtr[y][x]= aCell;
                cellArr[cellArrSize]= aCell;
                cellArrSize++;
        }
    }
}

void Castle::run()
{
    for(int i=0;i<(size.GetWidth()*size.GetHeight());i++)
    {
        cellArr[i]->run();
    }
}
