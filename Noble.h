#ifndef NOBLE_H_INCLUDED
#define NOBLE_H_INCLUDED

#include "Player.h"


class Noble : public Player
{
    public:
        Noble(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange);
        void run();

    private:
        int direction[4];
        bool moveTowardEnemy();
        void randomizeDirections();
        bool moveInDirection(int x, int y);
        void randomMove();
        bool north();
        bool south();
        bool east();
        bool west();

        void randomizeRouteArr();

};



#endif // NOBLE_H_INCLUDED
