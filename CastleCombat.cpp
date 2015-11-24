#include "CastleCombat.h"
#include "Castle.h"
#include "SettingsPanel.h"

Castle* castle;

ChangeSettings* changeSettings;
Rules* rules;
About* about;
ReturnToGame* returnToGamePane;
SettingsPanel* settingsPanel;


BEGIN_EVENT_TABLE(CastleCombat, wxFrame)
    EVT_CLOSE(CastleCombat::OnClose)
    EVT_TOOL(idplay,CastleCombat::OnStart)
    EVT_TOOL(idpause,CastleCombat::OnPause)
    EVT_TOOL(idfast,CastleCombat::OnFastForward)
    EVT_TOOL(idnewgame,CastleCombat::OnNewGame)
    EVT_TOOL(idsettings,CastleCombat::OnSettings)
    EVT_MEDIA_LOADED(idloadmusic,CastleCombat::OnMediaLoaded)
    EVT_MEDIA_PLAY(idplaymusic,CastleCombat::OnMediaPlay)
END_EVENT_TABLE()

CastleCombat::CastleCombat(const wxString& title): wxFrame(NULL, -1, title)
{
    populated = false;
    wasRunning = false;
    repaintnum = 10;

    wxBitmap play(wxT("playButton.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pause(wxT("pauseButton.png"), wxBITMAP_TYPE_PNG);
    wxBitmap playDisabled(wxT("playDisabled.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pauseDisabled(wxT("pauseDisabled.png"), wxBITMAP_TYPE_PNG);
    wxBitmap fastForward(wxT("fastForwardButton.png"), wxBITMAP_TYPE_PNG);
    wxBitmap newGame(wxT("newGame.png"), wxBITMAP_TYPE_PNG);
    wxBitmap settings(wxT("castleIcon.png"), wxBITMAP_TYPE_PNG);

    toolbar = new wxToolBar(this, idtoolbar, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxNO_BORDER, _T("ID_TOOLBAR1"));
    toolbar->AddTool(idplay, wxT("Play"), play, playDisabled);
    toolbar->SetToolShortHelp(idplay,"Play");
    toolbar->AddTool(idpause, wxT("Pause"), pause, pauseDisabled);
    toolbar->SetToolShortHelp(idpause,"Pause");
    toolbar->AddTool(idfast, wxT("FastForward"), fastForward);
    toolbar->SetToolShortHelp(idfast,"Fast Forward");
    toolbar->AddTool(idnewgame, wxT("New Game"), newGame);
    toolbar->SetToolShortHelp(idnewgame,"New Game");
    toolbar->AddStretchableSpace();
    toolbar->AddTool(idsettings, wxT("Settings"), settings);
    toolbar->SetToolShortHelp(idsettings,"Settings");

    toolbar->EnableTool(idpause,false);
    toolbar->EnableTool(idfast,false);
    toolbar->EnableTool(idnewgame,false);
    toolbar->Realize();
    SetToolBar(toolbar);

    sb = CreateStatusBar();
    sb->SetStatusText(wxT(""));

    readJsonSettings();
    castle = new Castle(this, dimX,dimY);

    changeSettings = new ChangeSettings(this,dimX,dimY);
    rules = new Rules(this,dimX,dimY);
    about = new About(this,dimX,dimY);
    returnToGamePane = new ReturnToGame(this,dimX,dimY);
    settingsPanel = new SettingsPanel(this,dimX,dimY);

    changeSettings->Hide();
    rules->Hide();
    about->Hide();
    returnToGamePane->Hide();
    settingsPanel->Hide();


    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(castle, 0, wxALIGN_CENTER);
    SetSizer(topSizer);

    SetStatusBarPane(-1);

    music = new wxMediaCtrl();
    music->Create(this,idmediactrl);
    music->Load("bubblebobble.mp3");

    Fit();

}

void CastleCombat::OnClose(wxCloseEvent &event)
{
    delete castle;
    delete changeSettings;
    delete rules;
    delete about;
    delete returnToGamePane;
    delete settingsPanel;
    delete music;
    delete topSizer;
    delete sb;
    delete toolbar;

    Destroy();
}

void CastleCombat::readJsonSettings()
{
    ifstream in("jsonSettings.json");
    in >> jsonSettings;
    dimX=jsonSettings["dx"].asInt();
    dimY=jsonSettings["dy"].asInt();
    in.close();
}

void CastleCombat::setJsonSettings(int x, int y)
{
    jsonSettings["dx"]=x;
    jsonSettings["dy"]=y;

    ofstream out("jsonSettings.json",std::ofstream::out);
    out << jsonSettings;
    out.close();
}

void CastleCombat::OnMediaLoaded(wxMediaEvent& event)
{
    music->Play();
    music->SetVolume(1.0);
}

void CastleCombat::OnMediaPlay(wxMediaEvent& event)
{

}

void CastleCombat::OnStart(wxCommandEvent &event)
{

    if(!populated)
    {
        castle->populateArena();
        populated=true;
    }

    castle->timer->Start();
    toolbar->EnableTool(idplay,false);
    toolbar->EnableTool(idpause,true);
    toolbar->EnableTool(idfast,true);
    toolbar->EnableTool(idnewgame,true);
    toolbar->EnableTool(idsettings,true);
}

void CastleCombat::OnPause(wxCommandEvent &event)
{
    castle->timer->Stop();
    toolbar->EnableTool(idplay,true);
    toolbar->EnableTool(idpause,false);
    toolbar->EnableTool(idfast,false);
    castle->status->SetStatusText(wxT("Paused"));
}

void CastleCombat::OnFastForward(wxCommandEvent &event)
{
    if(castle->repaint==10)
    {
        castle->repaint=5;
        castle->status->SetStatusText(wxT("Crazy Speed"));
        wxMilliSleep(1000);

    }
    else if(castle->repaint==5)
    {
        castle->repaint=1;
        castle->status->SetStatusText(wxT("Hyper Speed"));
        wxMilliSleep(1000);

    }
    else if(castle->repaint==1)
    {
        castle->repaint=10;
        castle->status->SetStatusText(wxT("Normal Speed"));
        wxMilliSleep(1000);
    }
    repaintnum = castle->repaint;
}

void CastleCombat::OnNewGame(wxCommandEvent &event)
{
    changeSettings->Hide();
    rules->Hide();
    about->Hide();
    returnToGamePane->Hide();
    delete castle;
    castle = new Castle(this,dimX,dimY);
    castle->repaint=repaintnum;
    populated=false;
    topSizer->Add(castle, 0, wxALIGN_CENTER);
    SetSizer(topSizer);

    Fit();

    castle->OnPaint();
    toolbar->EnableTool(idplay,true);
    toolbar->EnableTool(idpause,false);
    toolbar->EnableTool(idfast,false);
    toolbar->EnableTool(idnewgame,false);
    toolbar->EnableTool(idsettings,true);
}

void CastleCombat::OnSettings(wxCommandEvent &event)
{
    castle->paintSettings();
    castle->paintSettings();

    changeSettings->Show();
    rules->Show();
    about->Show();
    returnToGamePane->Show();

    changeSettings->OnPaint();
    rules->OnPaint();
    about->OnPaint();
    returnToGamePane->OnPaint();

    if(castle->timer->IsRunning())
    {
        castle->timer->Stop();
        wasRunning=true;

    }

    castle->Hide();

    getStatus = castle->status->GetStatusText();
    castle->status->SetStatusText(wxT("Settings"));
    toolbar->EnableTool(idplay,false);
    toolbar->EnableTool(idpause,false);
    toolbar->EnableTool(idfast,false);
    toolbar->EnableTool(idnewgame,false);
    toolbar->EnableTool(idsettings,false);

}

void CastleCombat::OnReturnToGame()
{
    changeSettings->Hide();
    rules->Hide();
    about->Hide();
    returnToGamePane->Hide();
    if(wasRunning)
    {
        castle->timer->Start();
        toolbar->EnableTool(idplay,false);
        toolbar->EnableTool(idpause,true);
        toolbar->EnableTool(idfast,true);
        toolbar->EnableTool(idnewgame,true);
        toolbar->EnableTool(idsettings,true);
        wasRunning=false;
    }
    else
    {
        castle->OnPaint();
        toolbar->EnableTool(idplay,true);
        toolbar->EnableTool(idpause,false);
        toolbar->EnableTool(idfast,false);
        toolbar->EnableTool(idnewgame,false);
        toolbar->EnableTool(idsettings,true);
    }
    castle->status->SetStatusText(getStatus);
}

void CastleCombat::showSettings()
{

    changeSettings->Hide();
    rules->Hide();
    about->Hide();
    returnToGamePane->Hide();


    settingsPanel->Show();
}

void CastleCombat::backToSettings()
{
    settingsPanel->Hide();
    castle->Show();
    castle->OnPaint();
    wxCommandEvent event;
    OnSettings(event);
}

void CastleCombat::saveSettings(int x, int y)
{
    dimX=x;
    dimY=y;

    setJsonSettings(x,y);

    delete changeSettings;
    changeSettings = new ChangeSettings(this,x,y);
    changeSettings->Hide();

    delete rules;
    rules = new Rules(this,x,y);
    rules->Hide();

    delete about;
    about = new About(this,x,y);
    about->Hide();

    delete returnToGamePane;
    returnToGamePane = new ReturnToGame(this,x,y);
    returnToGamePane->Hide();

    delete settingsPanel;
    settingsPanel = new SettingsPanel(this,x,y);
    settingsPanel->Hide();

    wxCommandEvent event;
    OnNewGame(event);


}


