#ifndef CELL_H
#define CELL_H

#include <wx/wx.h>
#include <wx/utils.h>
#include <string>
#include "Castle.h"


using std::string;

class Cell
{
    public:
        string type, name, iconFile, healthFile;
        bool ran;

        Cell();
        Cell(wxPoint point, string type, string name, string iconFile, string healthFile);
        virtual ~Cell();
        int getX();
        int getY();
        virtual void run();
        virtual void missHit(){};
        virtual void takeDamage(int hit){};
        void setCoordinates(wxPoint point);

    private:
        wxPoint point;



};

extern Cell*** cellPtr;
#endif // CELL_H
