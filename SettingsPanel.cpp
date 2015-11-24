#include "SettingsPanel.h"
#include "Castle.h"

BEGIN_EVENT_TABLE(SettingsPanel, wxPanel)
    EVT_BUTTON(idcancel,SettingsPanel::OnCancel)
    EVT_BUTTON(idsave,SettingsPanel::OnSave)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(ChangeSettings, wxPanel)
    EVT_ENTER_WINDOW(ChangeSettings::OnEnter)
    EVT_LEAVE_WINDOW(ChangeSettings::OnLeave)
    EVT_LEFT_UP(ChangeSettings::OnClick)
    EVT_ERASE_BACKGROUND(ChangeSettings::OnErase)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Rules, wxPanel)
    EVT_ENTER_WINDOW(Rules::OnEnter)
    EVT_LEAVE_WINDOW(Rules::OnLeave)
    EVT_LEFT_UP(Rules::OnClick)
    EVT_ERASE_BACKGROUND(Rules::OnErase)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(About, wxPanel)
    EVT_ENTER_WINDOW(About::OnEnter)
    EVT_LEAVE_WINDOW(About::OnLeave)
    EVT_LEFT_UP(About::OnClick)
    EVT_ERASE_BACKGROUND(About::OnErase)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(ReturnToGame, wxPanel)
    EVT_ENTER_WINDOW(ReturnToGame::OnEnter)
    EVT_LEAVE_WINDOW(ReturnToGame::OnLeave)
    EVT_LEFT_UP(ReturnToGame::OnClick)
    EVT_ERASE_BACKGROUND(ReturnToGame::OnErase)
END_EVENT_TABLE()

SettingsPanel::SettingsPanel(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize((x+2)*32,((y+2)*32)), wxTAB_TRAVERSAL)
{
    this->x=((x+2)*32);
    this->y=((y+2)*32);
    this->parent=(CastleCombat*)parent;

    wxArrayString dimensions;

    for(int i=5;i!=16;i++)
    {
        dimensions.Add(wxString::Format(wxT("%i"),i));
    }

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);

    xlabel = new wxStaticText(this, wxID_ANY, "X Dimension");
    ylabel = new wxStaticText(this, wxID_ANY, "Y Dimension");

    xChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, dimensions,0, wxDefaultValidator,"");
    yChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, dimensions,0, wxDefaultValidator,"");
    xChoice->SetSelection(this->parent->dimX-5);
    yChoice->SetSelection(this->parent->dimY-5);

    cancelButton = new wxButton(this, idcancel, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    saveButton = new wxButton(this, idsave, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));

    sizer1->Add(xlabel,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer1->Add(xChoice,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);


    sizer2->Add(ylabel,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer2->Add(yChoice,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    sizer3->Add(cancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer3->Add(saveButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    topSizer->Add(sizer1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    topSizer->Add(sizer2,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    topSizer->Add(sizer3, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);

    SetSizer(topSizer);
    Layout();

    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

}

SettingsPanel::~SettingsPanel()
{

}

void SettingsPanel::OnPaint()
{
    wxClientDC dc(this);
    wxString text = "Settings";
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void SettingsPanel::OnErase(wxEraseEvent& event)
{

}

void SettingsPanel::OnCancel(wxCommandEvent &event)
{
    parent->backToSettings();
}

void SettingsPanel::OnSave(wxCommandEvent &event)
{
    parent->saveSettings(xChoice->GetCurrentSelection()+5,yChoice->GetCurrentSelection()+5);

}

void SettingsPanel::setDimensions(int x, int y)
{
    this->x=x+2;
    this->y=y+2;
    SetSize((x+2)*32, (y+2)*32);
}

ChangeSettings::ChangeSettings(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize((x+2)*32,((y+2)*32)/4), wxFULL_REPAINT_ON_RESIZE)
{
    this->x=((x+2)*32);
    this->y=((y+2)*32)/4;
    this->parent=(CastleCombat*)parent;

}

ChangeSettings::~ChangeSettings()
{

}

void ChangeSettings::OnErase(wxEraseEvent& event)
{

}

void ChangeSettings::OnPaint()
{
    wxClientDC dc(this);
    wxString text = "Settings";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void ChangeSettings::OnEnter(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Settings";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxLIGHT_GREY);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void ChangeSettings::OnLeave(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Settings";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));

}

void ChangeSettings::OnClick(wxMouseEvent &event)
{
    parent->showSettings();
}

void ChangeSettings::setDimensions(int x, int y)
{
    this->x=x+2;
    this->y=y+2;
    SetSize((x+2)*32, (y+2)*32);
}

Rules::Rules(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxPoint(0,((y+2)*32)/4), wxSize((x+2)*32,((y+2)*32)/4), wxFULL_REPAINT_ON_RESIZE)
{
    this->x=((x+2)*32);
    this->y=((y+2)*32)/4;
    this->parent=(CastleCombat*)parent;

}

Rules::~Rules()
{

}

void Rules::OnErase(wxEraseEvent& event)
{

}

void Rules::OnPaint()
{
    wxClientDC dc(this);
    wxString text = "Rules";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void Rules::OnEnter(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Rules";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxLIGHT_GREY);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void Rules::OnLeave(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Rules";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));

}

void Rules::OnClick(wxMouseEvent &event)
{
}

void Rules::setDimensions(int x, int y)
{
    this->x=x+2;
    this->y=y+2;
    SetSize((x+2)*32, (y+2)*32);
}

About::About(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxPoint(0,((y+2)*32)/2), wxSize((x+2)*32,((y+2)*32)/4), wxFULL_REPAINT_ON_RESIZE)
{
    this->x=((x+2)*32);
    this->y=((y+2)*32)/4;
    this->parent=(CastleCombat*)parent;

}

About::~About()
{

}

void About::OnErase(wxEraseEvent& event)
{

}

void About::OnPaint()
{
    wxClientDC dc(this);
    wxString text = "About";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void About::OnEnter(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "About";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxLIGHT_GREY);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void About::OnLeave(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "About";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));

}

void About::OnClick(wxMouseEvent &event)
{
}

void About::setDimensions(int x, int y)
{
    this->x=x+2;
    this->y=y+2;
    SetSize((x+2)*32, (y+2)*32);
}

ReturnToGame::ReturnToGame(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxPoint(0,(((y+2)*32)*3)/4), wxSize((x+2)*32,((y+2)*32)/4), wxFULL_REPAINT_ON_RESIZE)
{
    this->x=((x+2)*32);
    this->y=((y+2)*32)/4;
    this->parent=(CastleCombat*)parent;

}

ReturnToGame::~ReturnToGame()
{

}

void ReturnToGame::OnErase(wxEraseEvent& event)
{

}

void ReturnToGame::OnPaint()
{
    wxClientDC dc(this);
    wxString text = "Return to Game";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void ReturnToGame::OnEnter(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Return to Game";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxLIGHT_GREY);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));
}

void ReturnToGame::OnLeave(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxString text = "Return to Game";
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Courier");
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(text, wxPoint(x/2 - (dc.GetTextExtent(text).x)/2,y/2));

}

void ReturnToGame::OnClick(wxMouseEvent &event)
{
    this->Hide();
    castle->Show();

    parent->OnReturnToGame();
}

void ReturnToGame::setDimensions(int x, int y)
{
    this->x=x+2;
    this->y=y+2;
    SetSize((x+2)*32, (y+2)*32);
}
