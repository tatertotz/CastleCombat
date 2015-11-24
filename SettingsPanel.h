#ifndef SETTINGSPANEL_H_INCLUDED
#define SETTINGSPANEL_H_INCLUDED
#include <wx/wx.h>
#include "CastleCombat.h"

class SettingsPanel : public wxPanel
{
    private:
        int x,y;
        wxStaticText* xlabel;
        wxStaticText* ylabel;

        wxChoice* xChoice;
        wxChoice* yChoice;

        wxButton* cancelButton;
        wxButton* saveButton;
        CastleCombat* parent;

    public:
        SettingsPanel(wxFrame *parent, int x, int y);
        ~SettingsPanel();
        void OnPaint();
        void OnErase(wxEraseEvent& event);
        void OnCancel(wxCommandEvent &event);
        void OnSave(wxCommandEvent &event);
        void setDimensions(int,int);

        enum
        {
            idcancel,
            idsave
        };

        DECLARE_EVENT_TABLE()


};

class ChangeSettings : public wxPanel
{
    private:
        int x,y;
        CastleCombat* parent;

    public:
        ChangeSettings(wxFrame *parent, int x, int y);
        ~ChangeSettings ();
        void OnPaint();
        void OnErase(wxEraseEvent& event);
        void OnEnter(wxMouseEvent& event);
        void OnLeave(wxMouseEvent& event);
        void OnClick(wxMouseEvent &event);
        void setDimensions(int,int);

        DECLARE_EVENT_TABLE()

};

class Rules : public wxPanel
{
    private:
        int x,y;
        CastleCombat* parent;

    public:
        Rules(wxFrame *parent, int x, int y);
        ~Rules();
        void OnPaint();
        void OnErase(wxEraseEvent& event);
        void OnEnter(wxMouseEvent& event);
        void OnLeave(wxMouseEvent& event);
        void OnClick(wxMouseEvent &event);
        void setDimensions(int,int);

        DECLARE_EVENT_TABLE()

};

class About : public wxPanel
{
    private:
        int x,y;
        CastleCombat* parent;

    public:
        About(wxFrame *parent, int x, int y);
        ~About();
        void OnPaint();
        void OnErase(wxEraseEvent& event);
        void OnEnter(wxMouseEvent& event);
        void OnLeave(wxMouseEvent& event);
        void OnClick(wxMouseEvent &event);
        void setDimensions(int,int);

        DECLARE_EVENT_TABLE()

};



class ReturnToGame : public wxPanel
{
    private:
        int x,y;
        CastleCombat* parent;

    public:
        ReturnToGame(wxFrame *parent, int x, int y);
        ~ReturnToGame();
        void OnErase(wxEraseEvent& event);
        void OnPaint();
        void OnEnter(wxMouseEvent& event);
        void OnLeave(wxMouseEvent& event);
        void OnClick(wxMouseEvent &event);
        void setDimensions(int,int);

        DECLARE_EVENT_TABLE()

};


#endif // SETTINGSPANEL_H_INCLUDED
