#include "Noble.h"

Noble::Noble(wxPoint point, string type, string name, string iconFile, string healthFile, string attackFile, string defendFile, int hp, int minHit, int maxHit, int attackRange) : Player(point,type,name,iconFile,healthFile, attackFile, defendFile,hp, minHit,maxHit, attackRange)
{
    direction[0]=1;
    direction[1]=2;
    direction[2]=3;
    direction[3]=4;
}

void Noble::run()
{
    if(!ran)
    {
        if(isEnemyInRange("Villager"))
        {
            attack();
        }
        else
        {
             if(name=="king" || !moveTowardEnemy())
                randomMove();

            for(int i=0;i<castle->repaint;i++)
            {
                castle->OnPaint();
            }
            ran=true;
        }
    }
    else
        ran=false;

}

bool Noble::moveTowardEnemy()
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
            if(castle->isInBounds(getY()-i,ns) && cellPtr[getY()-i][ns]->type=="Villager")
            {
                return moveInDirection(getX(),getY()-1);
            }
            if(castle->isInBounds(getY()+i,ns) && cellPtr[getY()+i][ns]->type=="Villager")
            {
                return moveInDirection(getX(),getY()+1);
            }
        }

        for(int ew = getY()-i; ew <= getY()+i; ew++) //check east and west sides of square in range
        {
            if(castle->isInBounds(ew,getX()+i) && cellPtr[ew][getX()+i]->type=="Villager")
            {
                return moveInDirection(getX()+1,getY());
            }
            if(castle->isInBounds(ew,getX()-i) && cellPtr[ew][getX()-i]->type=="Villager")
            {
                return moveInDirection(getX()-1,getY());
            }
        }
    }
    return false;
}

void Noble::randomizeDirections()
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

void Noble::randomMove()
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

bool Noble::moveInDirection(int xx, int yy)
{
    if(cellPtr[yy][xx]->name=="floor")
    {
        if(name == "king")
        {
            if(yy>castle->dy/2)
                return false;
            castle->kingPosition=wxPoint(xx,yy);
        }
        swapCells(yy,xx);
        return true;
    }

    return false;
}

