#ifndef CASTLE_H
#define CASTLE_H
#include "Cell.h"
#include <wx/wx.h>

class Castle : public wxPanel
{
    public:
        Castle(wxFrame *parent);
        virtual ~Castle();
        void setDimensions(wxSize size);
        wxSize getDimensions();
        void run();
    protected:
    private:
        wxSize size;
        int cellArrSize;
        Cell*** cellPtr;
        Cell** cellArr;
        void build();
};

#endif // CASTLE_H
