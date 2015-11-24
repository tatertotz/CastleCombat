#include "Door.h"
#include "Villager.h"

Door::Door(wxPoint point, string type, string name, string iconFile, string healthFile,int villagers) : Cell(point,type,name,iconFile,healthFile)
{
    remainingVillagers = villagers;
}

void Door::run()
{
    int spawnX, spawnY;
    bool go = false;
    if(castle->villagerArr.size() != 0 && cellPtr[getY()-1][getX()]->name=="floor")
    {
        spawnX=getX();
        spawnY=getY()-1;
        go=true;
    }
    else if(castle->isInBounds(getY(),getX()+1) && castle->villagerArr.size() != 0 && cellPtr[getY()][getX()+1]->name=="floor")
    {
        spawnX=getX()+1;
        spawnY=getY();
        go=true;
    }
    else if(castle->isInBounds(getY(),getX()-1) && castle->villagerArr.size() != 0 && cellPtr[getY()][getX()-1]->name=="floor")
    {
        spawnX=getX()-1;
        spawnY=getY();
        go=true;
    }
    if(go)
    {
        remainingVillagers--;
        string icon = iconFile;
        string n = castle->villagerArr.back();
        castle->villagerArr.pop_back();
        wxString nn = n+"Door32.png";

        iconFile = nn;
        healthFile = nn;
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

        iconFile = icon;
        healthFile = iconFile;
        delete cellPtr[spawnY][spawnX];

        nn = n+"32.png";
        string newType = n;
        string newIcon = string(nn.mb_str());


        if(newType=="warrior")
        {
            cellPtr[spawnY][spawnX] = new Villager(wxPoint(spawnX,spawnY),"Villager",newType,newIcon,"fullHealth.png","warriorAttack32.png","warriorDefend32.png",10,3,6,1);
        }
        else if(newType=="archer")
        {
            cellPtr[spawnY][spawnX] = new Villager(wxPoint(spawnX,spawnY),"Villager",newType,newIcon,"fullHealth.png","archerAttack32.png","archerDefend32.png",10,2,5,3);
        }
        else if(newType=="peasant")
        {
            cellPtr[spawnY][spawnX] = new Villager(wxPoint(spawnX,spawnY),"Villager",newType,newIcon,"fullHealth.png","peasantAttack32.png","peasantDefend32.png",10,1,4,2);
        }
        for(int i=0;i<castle->repaint;i++)
        {
            castle->OnPaint();
        }

    }
}
