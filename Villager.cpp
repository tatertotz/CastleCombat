#include "Villager.h"
#include "Pitfall.h"


Villager::Villager(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange) : Player(point,type,name,iconFile,healthFile,attackFile,defendFile,hp,minHit,maxHit,attackRange)
{
    direction[0]=1;
    direction[1]=2;
    direction[2]=3;
    direction[3]=4;

    inSafePit=false;
}


void Villager::run()
{
    //if(!ran)
    //{
        if(isKingInRange() || isEnemyInRange("Noble"))
        {
            attack();
        }
        else
        {
            if(!moveTowardEnemy())
                randomMove();

            for(int i=0;i<castle->repaint;i++)
            {
                castle->OnPaint();
            }
            //ran=true;
        }

    //}
    //else
        //ran=false;

}

bool Villager::moveTowardEnemy()
{
    int range;
    if(castle->dx > castle->dy)
        range = castle->dx;
    else
        range = castle->dy;

    for(int i = 1; i< range;i++)
    {
        for(int ns = getX()-i;ns <= getX()+i; ns++) //check north and south sides of square in range
        {
            if(castle->isInBounds(getY()-i,ns) && cellPtr[getY()-i][ns]->type=="Noble")
            {
                return moveInDirection(getX(),getY()-1);
            }
            if(castle->isInBounds(getY()+i,ns) && cellPtr[getY()+i][ns]->type=="Noble")
            {
                return moveInDirection(getX(),getY()+1);
            }
        }

        for(int ew = getY()-i; ew <= getY()+i; ew++) //check east and west sides of square in range
        {
            if(castle->isInBounds(ew,getX()+i) && cellPtr[ew][getX()+i]->type=="Noble")
            {
                return moveInDirection(getX()+1,getY());
            }
            if(castle->isInBounds(ew,getX()-i) && cellPtr[ew][getX()-i]->type=="Noble")
            {
                return moveInDirection(getX()-1,getY());
            }
        }
    }
    return false;
}

void Villager::randomizeDirections()
{
    for(int i=0;i<10;i++)
    {
        int randNum1=rand()%4;
        int randNum2=rand()%4;
        int temp = direction[randNum1];
        direction[randNum1]=direction[randNum2];
        direction[randNum2]=temp;
    }
}

void Villager::randomMove()
{

    randomizeDirections();

    for(int i=0;i<4;i++)
    {
        if(direction[i]==1 && moveInDirection(getX(),getY()-1))//move north
        {
            break;
        }
        else if(direction[i]==2 && moveInDirection(getX(),getY()+1))//move south
        {
            break;
        }
        else if(direction[i]==3 && moveInDirection(getX()+1,getY()))//move east
        {
            break;
        }
        else if(direction[i]==4 && moveInDirection(getX()-1,getY()))//move west
        {
            break;
        }
    }
}

bool Villager::moveInDirection(int xx, int yy)
{
    if(cellPtr[yy][xx]->name=="floor")
    {
        if(inSafePit)
            safePitToFloor(xx,yy);
        else
            swapCells(yy,xx);

        return true;
    }
    else if(cellPtr[yy][xx]->name=="pitfall")
    {
        takeItToThePit(name,getX(),getY(),xx,yy);
        return true;
    }

    return false;
}

void Villager::safePitToFloor(int xx, int yy)
{
    wxString icon = name + "32.png";
    iconFile = icon;
    inSafePit=false;

    delete cellPtr[yy][xx];
    cellPtr[yy][xx] = new Pitfall(wxPoint(xx,yy),"Obstacle","pitfall","pitfall32.png","pitfall32.png");
    swapCells(yy,xx);

}

void Villager::takeItToThePit(string n,int x, int y, int xx, int yy)
{
    int randNum = rand() % 2;
    if(randNum==0) //moving to unsafe pit
    {
        if(inSafePit)//moving from safe pit to unsafe pit
        {
            delete this;
            cellPtr[y][x]= new Pitfall(wxPoint(x,y),"Obstacle","pitfall","pitfall32.png","pitfall32.png");
            pitfallAnimation(n,xx,yy);
        }
        else //moving from floor to unsafe pit
        {
            delete this;
            cellPtr[y][x]= new Cell(wxPoint(x,y),"Transport","floor","floor32.png","floor32.png");
            pitfallAnimation(n,xx,yy);
        }
    }
    else //moving to safe pit
    {
        if(inSafePit)//moving from safe pit to safe pit
        {
            swapCells(yy,xx);
            for(int i=0;i<castle->repaint;i++)
            {
                castle->OnPaint();
            }

            for(int i=0;i<castle->repaint*15;i++)
            {
                castle->PaintCell("safe.png",xx,yy);
            }

        }
        else //moving from floor to safe pit
        {
            wxString icon = n + "Pit32.png";
            iconFile = icon;
            inSafePit=true;

            delete cellPtr[yy][xx];
            cellPtr[yy][xx]= new Cell(wxPoint(xx,yy),"Transport","floor","floor32.png","floor32.png");

            swapCells(yy,xx);

            for(int i=0;i<castle->repaint;i++)
            {
                castle->OnPaint();
            }

            for(int i=0;i<castle->repaint*15;i++)
            {
                castle->PaintCell("safe.png",xx,yy);
            }
        }
    }
}

void Villager::pitfallAnimation(string n, int xx, int yy)
{
        wxString nn = n+"Pit32.png";
        cellPtr[yy][xx]->iconFile=nn;
        cellPtr[yy][xx]->healthFile=nn;
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        nn = n+"OpenPit32.png";
        cellPtr[yy][xx]->iconFile=nn;
        cellPtr[yy][xx]->healthFile=nn;
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        cellPtr[yy][xx]->iconFile="skeliOpenPit32.png";
        cellPtr[yy][xx]->healthFile="skeliOpenPit32.png";
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        cellPtr[yy][xx]->iconFile="pitfallOpen32.png";
        cellPtr[yy][xx]->healthFile="pitfallOpen32.png";
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        cellPtr[yy][xx]->iconFile="pitfall32.png";
        cellPtr[yy][xx]->healthFile="pitfall32.png";

        castle->remVillagers--;
}
