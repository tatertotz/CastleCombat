#ifndef CASTLECOMBAT_H_INCLUDED
#define CASTLECOMBAT_H_INCLUDED

#include <time.h>
#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <fstream>
#include "json.h"

using std::ifstream;
using std::ofstream;

class CastleCombat : public wxFrame
{
    private:
        bool populated;
        wxMediaCtrl *music;
        bool wasRunning;
        wxString getStatus;
        wxBoxSizer* topSizer;
        int repaintnum;


    public:
        wxStatusBar *sb;
        Json::Value jsonSettings;
        int dimX, dimY;
        wxToolBar *toolbar;
        CastleCombat(const wxString& title);
        void OnClose(wxCloseEvent& event);
        void OnStart(wxCommandEvent &event);
        void OnPause(wxCommandEvent &event);
        void OnFastForward(wxCommandEvent &event);
        void OnSettings(wxCommandEvent &event);
        void OnNewGame(wxCommandEvent &event);
        void OnMediaLoaded(wxMediaEvent& event);
        void OnMediaPlay(wxMediaEvent& event);
        void OnReturnToGame();
        void readJsonSettings();
        void setJsonSettings(int x, int y);
        void showSettings();
        void backToSettings();
        void saveSettings(int, int);

        enum
        {
            idtoolbar,
            idplay,
            idpause,
            idfast,
            idnewgame,
            idsettings,
            idmediactrl,
            idloadmusic,
            idplaymusic
        };

        DECLARE_EVENT_TABLE()
};

#endif // CASTLECOMBAT_H_INCLUDED
