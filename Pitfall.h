#ifndef PITFALL_H_INCLUDED
#define PITFALL_H_INCLUDED

#include "Cell.h"

class Pitfall : public Cell
{
    public:
        Pitfall(wxPoint point, string type, string name, string iconFile, string healthFile);
};


#endif // PITFALL_H_INCLUDED
