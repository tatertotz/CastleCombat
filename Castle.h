#ifndef CASTLE_H
#define CASTLE_H

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <vector>

using std::vector;
using std::string;

class Castle : public wxPanel
{
    public:
        int dx, dy, totNobles, totVillagers, remNobles, remVillagers, repaint;
        vector<string> villagerArr;
        bool kingIsDead;
        wxPoint kingPosition;
        wxTimer* timer;
        wxStatusBar *status;
        wxString statusTxt;

        Castle(wxFrame *parent, int x, int y);
        ~Castle();
        void build();
        void populateArena();
        void OnErase(wxEraseEvent& event);
        void setDimensions(int dx, int dy);
        void run(wxCommandEvent &event);
        void updateStatus();
        void randomizeShuffleArr();
        bool test(string s, int y, int x);
        void OnPaint();
        void paintSettings();
        void PaintCell(string file, int x, int y);
        bool isInBounds(int y, int x);

    private:
        int cells, pitfalls;
        wxPoint* shuffleArr;
        wxBitmap getBitmap(int i, int j);

};

extern Castle* castle;


#endif // CASTLE_H
