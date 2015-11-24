#include "Castle.h"
#include "Cell.h"
#include "Noble.h"
#include "King.h"
#include "Villager.h"
#include "Pitfall.h"
#include "Door.h"

Cell*** cellPtr;

Castle::~Castle()
{
     delete timer;
     delete shuffleArr;

     for(int y=0;y<dy;y++)
     {
         for(int x=0;x<dx;x++)
         {
             delete cellPtr[y][x];
         }

         delete cellPtr[y];
     }

     delete cellPtr;

}

Castle::Castle(wxFrame* parent, int x, int y) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize((x+2)*32,(y+2)*32), wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);
    repaint = 10;

    this->dx = x+2;
    this->dy = y+2;
    cells = dx*dy;
    totNobles = 0.15*cells;
    totVillagers = 0.25*cells;
    pitfalls = 0.06*cells;
    kingIsDead = false;

    remNobles = totNobles;
    remVillagers = totVillagers;

    status= parent->GetStatusBar();
    shuffleArr = new wxPoint[cells];
    build();

    Connect(wxEVT_TIMER, wxCommandEventHandler(Castle::run));
    Connect(wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(Castle::OnErase));
}

void Castle::build()
{
    cellPtr = new Cell**[dy];
    int shuffleArrSize=0;
    for(int y=0;y<dy;y++)
    {
        cellPtr[y] = new Cell*[dx];
        for(int x =0;x<dx;x++)
        {
            if(y==0&&x==0)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle", "wall", "wallCornerNW32.png","wallCornerNW32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==0&&x==dx-1)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallCornerNE32.png","wallCornerNE32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==0)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallN32.png","wallN32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==1&&x==(dx-1)/2)
            {
                cellPtr[y][x]= new King(wxPoint(x,y),"Noble","king","king32.png","fullHealth.png","kingAttack32.png","kingDefend32.png",30,9,11,4);
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
                kingPosition = wxPoint(x,y);
            }
            else if(y==(dy-1)/2 && x==0)
            {
                cellPtr[y][x]= new Door(wxPoint(x,y),"Transport","door","leftDoor32.png","leftDoor32.png",remVillagers);
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(x==0&&y==dy-1)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallCornerSW32.png","wallCornerSW32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(x==0)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallW32.png","wallW32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(x==dx-1&&y==dy-1)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallCornerSE32.png","wallCornerSE32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==(dy-1)/2 && x==dx-1)
            {
                cellPtr[y][x]= new Door(wxPoint(x,y),"Transport","door","rightDoor32.png","rightDoor32.png",remVillagers);
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(x==dx-1)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallE32.png","wallE32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==dy-1 && x==(dx-1)/2)
            {
                cellPtr[y][x]= new Door(wxPoint(x,y),"Transport","door","leftDoor32.png","leftDoor32.png",remVillagers);
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==dy-1 && x==(dx-1)/2+1)
            {
                cellPtr[y][x]= new Door(wxPoint(x,y),"Transport","door","rightDoor32.png","rightDoor32.png",remVillagers);
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else if(y==dy-1)
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Obstacle","wall","wallS32.png","wallS32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            else
            {
                cellPtr[y][x]= new Cell(wxPoint(x,y),"Transport","floor","floor32.png","floor32.png");
                shuffleArr[shuffleArrSize]= wxPoint(x,y);
            }
            shuffleArrSize++;

        }
    }
}

void Castle::populateArena()
{
    randomizeShuffleArr();

    int pitCount = pitfalls;
    for(int i=0;i<cells;i++)
    {
        if(cellPtr[shuffleArr[i].y][shuffleArr[i].x]->name=="floor" &&
           (shuffleArr[i] != wxPoint((dx-1)/2,dy-2) &&
            shuffleArr[i] != wxPoint((dx-1)/2+1,dy-2) &&
            shuffleArr[i] != wxPoint((dx-2),(dy-1)/2) &&
            shuffleArr[i] != wxPoint(1,(dy-1)/2)) &&
           pitCount!=0)
        {
            wxPoint temp = shuffleArr[i];
            delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
            cellPtr[temp.y][temp.x] = new Pitfall(temp,"Obstacle","pitfall","pitfall32.png","pitfall32.png");
            pitCount--;
        }
        if(pitCount==0)
            break;
    }

    int nobleCount = totNobles-1;
    for(int i=0;i<cells;i++)
    {
        if(cellPtr[shuffleArr[i].y][shuffleArr[i].x]->name=="floor" && nobleCount!=0)
        {
            int r = rand() % 2;
            if(r==0)
            {
                wxPoint temp = shuffleArr[i];
                delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
                cellPtr[temp.y][temp.x] = new Noble(temp,"Noble","knight","knight32.png","fullHealth.png","knightAttack32.png","knightDefend32.png",10,4,7,1);
            }
            else
            {
                wxPoint temp = shuffleArr[i];
                delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
                cellPtr[temp.y][temp.x] = new Noble(temp,"Noble","ranger","ranger32.png","fullHealth.png","rangerAttack32.png","rangerDefend32.png",10,3,6,3);
            }

            nobleCount--;
        }
        if(nobleCount==0)
            break;
    }

    int villagerCount = totVillagers;

    for(int i=0;i<cells;i++)
    {
        if(shuffleArr[i].y>=dy/4 && cellPtr[shuffleArr[i].y][shuffleArr[i].x]->name=="floor" && villagerCount>totVillagers/2)
        {
            int r = rand() % 3;
            if(r==0)
            {
                wxPoint temp = shuffleArr[i];
                delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
                cellPtr[temp.y][temp.x] = new Villager(temp,"Villager","warrior","warrior32.png","fullHealth.png","warriorAttack32.png","warriorDefend32.png",10,3,6,1);
            }
            else if(r==1)
            {
                wxPoint temp = shuffleArr[i];
                delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
                cellPtr[temp.y][temp.x] = new Villager(temp,"Villager","archer","archer32.png","fullHealth.png","archerAttack32.png","archerDefend32.png",10,2,5,3);
            }
            else
            {
                wxPoint temp = shuffleArr[i];
                delete cellPtr[shuffleArr[i].y][shuffleArr[i].x];
                cellPtr[temp.y][temp.x] = new Villager(temp,"Villager","peasant","peasant32.png","fullHealth.png","peasantAttack32.png","peasantDefend32.png",10,1,4,2);
            }

            villagerCount--;
        }
        if(villagerCount == totVillagers/2)
            break;
    }

    while(villagerCount-- != 0)
    {
        int r = rand() % 3;
            if(r==0)
            {
                villagerArr.push_back("warrior");
            }
            else if(r==1)
            {
                villagerArr.push_back("archer");
            }
            else
            {
                villagerArr.push_back("peasant");
            }
    }
}

void Castle::run(wxCommandEvent &event)
{
    static int i =0;

    if(i==cells)
        i=0;

    if(i==0)
        randomizeShuffleArr();

    cellPtr[shuffleArr[i].y][shuffleArr[i].x]->run();

    updateStatus();

    if(remVillagers == 0)
    {
        statusTxt = "The Nobles are Victorious";

        status->SetStatusText(statusTxt);
        timer->Stop();
    }
    else if(kingIsDead)
    {
        statusTxt = "The King is Dead, the Villagers are Victorious";

        status->SetStatusText(statusTxt);
        timer->Stop();
    }

}

bool Castle::isInBounds(int y, int x)
{
    return (x >= 0 && x < dx && y >= 0 && y < dy);
}

void Castle::OnPaint()
{
    wxClientDC dc(this);

    for(int i=0;i<dy;i++)
    {
        for(int j=0;j<dx;j++)
        {
            wxBitmap bmp = getBitmap(i,j);
            dc.DrawBitmap(bmp, cellPtr[i][j]->getX()*32, cellPtr[i][j]->getY()*32, true);
        }
    }
}

wxBitmap Castle::getBitmap(int i, int j)
{
    wxMemoryDC memDC;

    wxBitmap bmp(32,32);
    wxBitmap bmp1(wxString(cellPtr[i][j]->iconFile),wxBITMAP_TYPE_PNG);
    wxBitmap bmp2(wxString(cellPtr[i][j]->healthFile),wxBITMAP_TYPE_PNG);

    memDC.SelectObject(bmp);
    memDC.Clear();
    memDC.DrawBitmap(bmp1,0,0, false);
    memDC.DrawBitmap(bmp2,0,0, true);
    memDC.SelectObject(wxNullBitmap);

    return bmp;
}

void Castle::paintSettings()
{
    wxClientDC dc(this);

    for(int i=0;i<dy;i++)
    {
        for(int j=0;j<dx;j++)
        {
            wxBitmap bmp ("settingsBackground.png",wxBITMAP_TYPE_PNG);
            dc.DrawBitmap(bmp, cellPtr[i][j]->getX()*32, cellPtr[i][j]->getY()*32, true);
        }
    }
}

void Castle::PaintCell(string file, int x, int y)
{
    wxClientDC dc(this);
    wxBitmap bmp (wxString(file),wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp, x*32, y*32, true);
}

void Castle::OnErase(wxEraseEvent& event)
{
}

void Castle::setDimensions(int dx, int dy)
{
    this->dx=dx+2;
    this->dy=dy+2;
    SetSize((dx+2)*32, (dy+2)*32);

    cells = dx*dy;
    totNobles = 0.15*cells;
    totVillagers = 0.3*cells;
    pitfalls = 0.06*cells;
    kingIsDead = false;

    remNobles = totNobles;
    remVillagers = totVillagers;
    shuffleArr = new wxPoint[cells];
}

void Castle::randomizeShuffleArr()
{
    for(int i=0; i<cells*100;i++)
    {
        int swap1 = rand() % cells;
        int swap2 = rand() % cells;

        wxPoint temp = shuffleArr[swap1];
        shuffleArr[swap1] = shuffleArr[swap2];
        shuffleArr[swap2] = temp;
    }
}

void Castle::updateStatus()
{
    statusTxt = "Nobles: " + wxString::Format(wxT("%d"), (int)remNobles) + "/" + wxString::Format(wxT("%d"), (int)totNobles) + " Villagers: "
             + wxString::Format(wxT("%d"), (int)remVillagers) + "/" + wxString::Format(wxT("%d"), (int)totVillagers);

    status->SetStatusText(statusTxt);
}
