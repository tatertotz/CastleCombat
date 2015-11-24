#include "King.h"

King::King(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange) : Noble(point,type,name,iconFile,healthFile, attackFile, defendFile,hp, minHit,maxHit, attackRange)
{

}

void King::takeDamage(int hit)
{
    hp=hp-hit;

    string hitFile = (string)wxString::Format(wxT("%d"), (int)hit) + "Hit.png";
    for(int i=0;i<castle->repaint*10;i++)
    {
        castle->PaintCell(hitFile,getX(),getY());
    }

    if(hp<=0)
    {
        castle->kingIsDead = true;

        int yy = getY();
        int xx = getX();

        iconFile = "skeli32.png";
        healthFile = "skeli32.png";
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        delete this;
        cellPtr[yy][xx]= new Cell(wxPoint(xx,yy),"Transport","floor","floor32.png","floor32.png");

        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }
    }
    else
    {
        if(hp>=29&&hp<=30)
        {
            healthFile = "fullHealth.png";
        }
        else if(hp>=26&&hp<=28)
        {
            healthFile = "9Health.png";
        }
        else if(hp>=23&&hp<=25)
        {
            healthFile = "8Health.png";
        }
        else if(hp>=20&&hp<=22)
        {
            healthFile = "7Health.png";
        }
        else if(hp>=17&&hp<=19)
        {
            healthFile = "6Health.png";
        }
        else if(hp>=14&&hp<=16)
        {
            healthFile = "5Health.png";
        }
        else if(hp>=11&&hp<=13)
        {
            healthFile = "4Health.png";
        }
        else if(hp>=8&&hp<=10)
        {
            healthFile = "3Health.png";
        }
        else if(hp>=4&&hp<=7)
        {
            healthFile = "2Health.png";
        }
        else if(hp>=1&&hp<=3)
        {
            healthFile = "1Health.png";
        }

    }

}
