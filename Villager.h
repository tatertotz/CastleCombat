#ifndef VILLAGER_H_INCLUDED
#define VILLAGER_H_INCLUDED

#include "Player.h"

class Villager : public Player
{
    public:
        Villager(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit,int maxHit, int attackRange);
        void run();

    private:
        bool inSafePit;
        int direction[4];
        void randomizeDirections();
        bool moveTowardEnemy();
        bool moveInDirection(int x, int y);
        void randomMove();
        void safePitToFloor(int x, int y);
        void takeItToThePit(string n, int x, int y, int xx, int yy);
        void pitfallAnimation(string n, int xx, int yy);
};



#endif // VILLAGER_H_INCLUDED
