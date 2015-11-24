#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Cell.h"

class Door : public Cell
{
    public:
        Door(wxPoint point, string type, string name, string iconFile, string healthFile, int villagers);
        void run();

    private:
        int remainingVillagers;
};


#endif // DOOR_H_INCLUDED
