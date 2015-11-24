#include "Player.h"
#include "Pitfall.h"
#include <cmath>

Player::Player(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange) : Cell(point,type,name,iconFile,healthFile)
{
    this->hp = hp;
    this->minHit = minHit;
    this->maxHit = maxHit;
    this->attackFile = attackFile;
    this->defendFile = defendFile;
    this->attackRange = attackRange;
}

void Player::swapCells(int yy, int xx)
{
    int x=getX();
    int y=getY();
    Cell* temp = this;
    cellPtr[y][x] = cellPtr[yy][xx];
    cellPtr[yy][xx] = temp;

    cellPtr[y][x]->setCoordinates(wxPoint(x,y));
    cellPtr[yy][xx]->setCoordinates(wxPoint(xx,yy));
}

bool Player::isKingInRange()
{
    if( std::abs(getX()-castle->kingPosition.x) <= attackRange && std::abs(getY()-castle->kingPosition.y) <= attackRange)
    {
        enemyLocation = castle->kingPosition;
        return true;
    }
    return false;
}

bool Player::isEnemyInRange(string enemyType)
{
    for(int i = 1; i<=attackRange;i++)
    {
        for(int ns = getX()-i;ns <= getX()+i; ns++) //check north and south sides of square in range
        {
            if(castle->isInBounds(getY()-i,ns) && cellPtr[getY()-i][ns]->type==enemyType)
            {
                enemyLocation = wxPoint(ns,getY()-i);
                return true;
            }
            if(castle->isInBounds(getY()+i,ns) && cellPtr[getY()+i][ns]->type==enemyType)
            {
                enemyLocation = wxPoint(ns,getY()+i);
                return true;
            }
        }

        for(int ew = getY()-i; ew <= getY()+i; ew++) //check east and west sides of square in range
        {
            if(castle->isInBounds(ew,getX()+i) && cellPtr[ew][getX()+i]->type==enemyType)
            {
                enemyLocation = wxPoint(getX()+i,ew);
                return true;
            }
            if(castle->isInBounds(ew,getX()-i) && cellPtr[ew][getX()-i]->type==enemyType)
            {
                enemyLocation = wxPoint(getX()-i,ew);
                return true;
            }

        }
    }

    return false;
}


void Player::attack()
{
    string tmpThisIconFile = iconFile;
    iconFile = attackFile;

    string tmpEnemyIconFile = cellPtr[enemyLocation.y][enemyLocation.x]->iconFile;

    if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "archer")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "archerDefend32.png";
    }
    else if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "warrior")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "warriorDefend32.png";
    }
    else if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "peasant")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "peasantDefend32.png";
    }
    else if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "king")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "kingDefend32.png";
    }
    else if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "knight")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "knightDefend32.png";
    }
    else if(cellPtr[enemyLocation.y][enemyLocation.x]->name == "ranger")
    {
        cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = "rangerDefend32.png";
    }

    for(int i=0;i<castle->repaint;i++)
    {
        castle->OnPaint();
    }

    iconFile = tmpThisIconFile;
    cellPtr[enemyLocation.y][enemyLocation.x]->iconFile = tmpEnemyIconFile;

    for(int i=0;i<castle->repaint;i++)
    {
        castle->OnPaint();
    }

    int miss = rand() % 10;
    if(miss==0 && name!= "king")
        cellPtr[enemyLocation.y][enemyLocation.x]->missHit();
    else
    {
        int randHit = rand() % (maxHit-minHit)+minHit;
        cellPtr[enemyLocation.y][enemyLocation.x]->takeDamage(randHit);
    }

}

void Player::missHit()
{
    string hitFile = "miss.png";
    for(int i=0;i<castle->repaint*15;i++)
    {
        castle->PaintCell(hitFile,getX(),getY());
    }
}

void Player::takeDamage(int hit)
{
    hp=hp-hit;

    string hitFile = (string)wxString::Format(wxT("%d"), (int)hit) + "Hit.png";
    for(int i=0;i<castle->repaint*10;i++)
    {
        castle->PaintCell(hitFile,getX(),getY());
    }

    if(hp<=0)
    {
        int x = getX();
        int y = getY();
        Cell *newCell;
        if(type=="Villager")
        {
            wxString n = name + "Pit32.png";
            if(iconFile == n)
            {
                newCell = new Pitfall(wxPoint(getX(),getY()),"Obstacle","pitfall","pitfall32.png","pitfall32.png");
                iconFile = "skeliPit32.png";
                healthFile = "skeliPit32.png";
            }
            else
            {
                newCell = new Cell(wxPoint(getX(),getY()),"Transport","floor","floor32.png","floor32.png");
                iconFile = "skeli32.png";
                healthFile = "skeli32.png";
            }
            castle->remVillagers--;
        }
        else
        {
            newCell = new Cell(wxPoint(getX(),getY()),"Transport","floor","floor32.png","floor32.png");
            iconFile = "skeli32.png";
            healthFile = "skeli32.png";
            castle->remNobles--;
        }


        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        delete this;
        cellPtr[y][x]= newCell;

        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }
    }
    else
    {
        wxString h = wxString::Format(wxT("%i"),hp);
        healthFile = h+"Health.png";
    }

}
