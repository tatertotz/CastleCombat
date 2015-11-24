#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Cell.h"

class Player : public Cell
{
    public:
        int hp, minHit, maxHit, attackRange;
        string attackFile, defendFile;
        wxPoint enemyLocation;

        Player(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange);
        void swapCells(int yy, int xx);
        bool isKingInRange();
        bool isEnemyInRange(string enemyType);
        void attack();
        void missHit();
        virtual void takeDamage(int hit);
};



#endif // PLAYER_H_INCLUDED
