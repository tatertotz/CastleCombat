#ifndef KING_H_INCLUDED
#define KING_H_INCLUDED

#include "Noble.h"

class King : public Noble
{
    public:
        King(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit,int maxHit, int attackRange);

        void takeDamage(int hit);

};

#endif // KING_H_INCLUDED
