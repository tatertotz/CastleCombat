#include "main.h"
#include "Castle.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    srand(time(NULL));
    CastleCombat *frame = new CastleCombat(wxT("CastleCombat"));

    wxIcon icon(wxString("castleIcon.png"),wxICON_DEFAULT_TYPE,32,32);
    frame->SetIcon(icon);
    frame->Show(true);
    castle->OnPaint();

    return true;
}
