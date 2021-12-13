//
//  Dungeon.cpp
//  CS32 Project 3
//
//  Created by Siyuan Li on 5/15/20.
//  Copyright © 2020 Siyuan Li. All rights reserved.
#include "Dungeon.h"
#include "Objects.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Dungeon::Dungeon(int l, player* p)
:level(l)
{
    //set all boolean member to deault false;
    setFight(false);
    setDrop(false);
    setisHit(false);
    setDisplay(false);
    setisBeat(false);
    setisHurt(false);
    
    //place walls;
           for (int r = 0; r < MAXROWS; r++)
           {
            for (int c = 0; c < MAXCOLS; c++)
            {
             playGround[r][c] = '#';
            }
           };
           
    //generate rooms;
           vector<center> centerv;
           
           int numNeighbour = randInt(3, 4);
           for (int i = 0; i < numNeighbour; i++)
           {
            int numLevel = randInt(1, 2);
            int maxHeight = (MAXROWS-3) / numLevel;
            int maxWidth = (MAXCOLS-6) / numNeighbour;


            for (int j = 0; j < numLevel; j++)
            {
             int centerR = j * maxHeight + randInt(3*maxHeight / 10, 7 * maxHeight / 10 );
             int centerC = i * maxWidth + randInt(3*maxWidth / 10 , 7 * maxWidth / 10 );
                
             int upMost = randInt(2, (centerR - j * maxHeight) - 1);
             int downMost = randInt(2, (j+1) * maxHeight - centerR - 1);
             int rightMost = randInt(3, (i+1) * maxWidth - centerC - 1);
             int leftMost = randInt(3, (centerC - i * maxWidth) - 1);
                
             center pt;
             pt.centerRow = centerR;
             pt.centerCol = centerC;
                
             centerv.push_back(pt);
                
             for (int r = centerR - upMost; r < centerR + downMost; r++)
             {
              for (int c = centerC - leftMost; c < centerC + rightMost; c++)
              {
               if (r < MAXROWS && r > 0 && c < MAXCOLS && c > 0)
                  playGround[r][c] = ' ';
              }
             }
            }
           };

    //generate corridors;
           for (int i = 0; i != centerv.size() - 1; i++)
           {
                  center start = centerv[i];
                  center end = centerv[i+1];

                  int startRow, startCol, endRow, endCol;
                  if (start.centerRow < end.centerRow)
                  {
                   startRow = start.centerRow;
                   endRow = end.centerRow;
                  }
                  else
                  {
                   endRow = start.centerRow;
                   startRow = end.centerRow;
                  }
               
                  if (start.centerCol < end.centerCol)
                  {
                   startCol = start.centerCol;
                   endCol = end.centerCol;
                  }
                  else
                  {
                   endCol = start.centerCol;
                   startCol = end.centerCol;
                  }
               
                  for (int i = startRow; i <= endRow; i++)
                  {
                   playGround[i][startCol] = ' ';
                   playGround[i][endCol] = ' ';
                  }
               
                  for (int i = startCol; i <= endCol; i++)
                  {
                   playGround[startRow][i] = ' ';
                   playGround[endRow][i] = ' ';
                  }
           }
       
        
           /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //first level;
    if(p == nullptr)
    {
        int birthR = randInt(1,MAXROWS-2);
        int birthC = randInt(1,MAXCOLS-2);
        
        while (playGround[birthR][birthC] == '#')
        {
            birthR = randInt(1,MAXROWS-2);
            birthC = randInt(1,MAXCOLS-2);
        }
        
        int stairR = randInt(1,MAXROWS-2);
        int stairC = randInt(1,MAXCOLS-2);
        
        while ((stairR == birthR && stairC == birthC) || playGround[stairR][stairC] == '#')
        {
            stairR = randInt(1,MAXROWS-2);
            stairC = randInt(1,MAXCOLS-2);
        };
        
        m_player = new player(birthR, birthC);
        stairRow = stairR; stairCol = stairC;
        
        if(l == MAXLEVEL)
        {
            int idolR = randInt(1,MAXROWS-2);
            int idolC = randInt(1,MAXCOLS-2);
            while ((idolR == birthR && idolC == birthC) || playGround[stairR][stairC] == '#')
            {
                idolR = randInt(1,MAXROWS-2);
                idolC = randInt(1,MAXCOLS-2);
            };
            idolRow = idolR; idolCol = idolC;
        }
        
        //////////////////////////////Place some Objects/////////////////////////////////////
        int numObjects = randInt(2, 3);
        m_size = numObjects;
        string names[] = {"mace", "short sword","long sword","scroll of enhance armor", "scroll of strength", "scroll of enhance health", "scroll of enhance dexterity"};
        
        for(int i = 0; i < numObjects; i++)
        {
            int rand = randInt(0, 6);
            if(rand <= 2)
            {
                objects.push_back(new weapon(names[rand]));
            }
            else
            {
                objects.push_back(new scroll(names[rand]));
            }
        }
        
            for(int j = 0; j < objects.size();j++)
            {
                int objR = randInt(1,MAXROWS-2);
                int objC = randInt(1,MAXCOLS-2);
                if (l != MAXLEVEL)
                {
                    while ((objR == birthR && objC == birthC) || (objR == stairR && objC == stairC) || playGround[objR][objC] == '#')
                    {
                        objR = randInt(1,MAXROWS-2);
                        objC = randInt(1,MAXCOLS-2);
                    }
                }else
                {
                    while ((objR == birthR && objC == birthC) || (objR == idolRow && objC == idolCol) || playGround[objR][objC] == '#')
                    {
                        objR = randInt(1,MAXROWS-2);
                        objC = randInt(1,MAXCOLS-2);
                    }
                }
                objects[j]->setR(objR); objects[j]->setC(objC);
            }
        /////////////////////////////////////Place some monsters///////////////////////////////////////
        others.clear();
            int numMons = randInt(2, 5 * (level + 1) + 1);
        
            for (int i = 0; i < numMons; i++)
            {
                int monR = randInt(1, MAXROWS-2);
                int monC = randInt(1, MAXCOLS-2);
                    
                while (playGround[monR][monC] == '#' || playGround[monR][monC] == '&' || playGround[monR][monC] == '>' || playGround[monR][monC] == '@' ||playGround[monR][monC] == ')'||playGround[monR][monC] == '?' || ((monR == birthR)&&(monC == birthC)))
                {
                    monR = randInt(1, MAXROWS-2);
                    monC = randInt(1, MAXCOLS-2);
                };
                if (level < 2)
                {
                    int kind = randInt(1, 2);
                    switch (kind)
                    {
                    case 1:
                        others.push_back(new goblin(monR, monC));
                        break;
                    case 2:
                        others.push_back(new snake(monR, monC));
                        break;
                    }
                }
                else if (level < 3)
                {
                    int kind = randInt(1, 3);
                    switch (kind)
                    {
                    case 1:
                        others.push_back(new bogeymen(monR, monC));
                        break;
                    case 2:
                        others.push_back(new snake(monR, monC));
                        break;
                    case 3:
                        others.push_back(new goblin(monR, monC));
                        break;
                    }
                }
                else
                {
                    int kind = randInt(1, 4);
                    switch (kind)
                    {
                    case 1:
                        others.push_back(new bogeymen(monR, monC));
                        break;
                    case 2:
                        others.push_back(new snake(monR, monC));
                        break;
                    case 3:
                        others.push_back(new dragon(monR, monC));
                        break;
                    case 4:
                        others.push_back(new goblin(monR, monC));
                        break;
                    }
                }
                
            }

        ////////////////////////////////////Finish placing monsters/////////////////////////////////////
        
        
    }
    else //not the first level;
    {
        int birthR = randInt(1,MAXROWS-2);
        int birthC = randInt(1,MAXCOLS-2);
        
        while (playGround[birthR][birthC] == '#')
        {
            birthR = randInt(1,MAXROWS-2);
            birthC = randInt(1,MAXCOLS-2);
        }
        
        int stairR = randInt(1,MAXROWS-2);
        int stairC = randInt(1,MAXCOLS-2);
        
        while ((stairR == birthR && stairC == birthC) || playGround[stairR][stairC] == '#')
        {
            stairR = randInt(1,MAXROWS-2);
            stairC = randInt(1,MAXCOLS-2);
        };
        
        m_player = p;
        m_player->setRow(birthR);
        m_player->setCol(birthC);
        stairRow = stairR; stairCol = stairC;
        
        if(l == MAXLEVEL)
        {
            int idolR = randInt(1,MAXROWS-2);
            int idolC = randInt(1,MAXCOLS-2);
            while ((idolR == birthR && idolC == birthC) || playGround[idolR][idolC] == '#')
            {
                idolR = randInt(1,MAXROWS-2);
                idolC = randInt(1,MAXCOLS-2);
            };
            idolRow = idolR; idolCol = idolC;
        }
        
        int numObjects = randInt(2, 3);
        m_size = numObjects;
        string names[] = {"mace", "short sword","long sword","scroll of enhance armor", "scroll of strength", "scroll of enhance health", "scroll of enhance dexterity"};
        
        for(int i = 0; i < numObjects; i++)
        {
            int rand = randInt(0, 6);
            if(rand <= 2)
            {
                objects.push_back(new weapon(names[rand]));
            }
            else
            {
                objects.push_back(new scroll(names[rand]));
            }
        }
        
            for(int j = 0; j < objects.size();j++)
            {
                int objR = randInt(1,MAXROWS-2);
                int objC = randInt(1,MAXCOLS-2);
                if (l != MAXLEVEL)
                {
                    while ((objR == birthR && objC == birthC) || (objR == stairR && objC == stairC) || playGround[objR][objC] == '#')
                    {
                        objR = randInt(1,MAXROWS-2);
                        objC = randInt(1,MAXCOLS-2);
                    }
                }else
                {
                    while ((objR == birthR && objC == birthC) || (objR == idolRow && objC == idolCol) || playGround[objR][objC] == '#')
                    {
                        objR = randInt(1,MAXROWS-2);
                        objC = randInt(1,MAXCOLS-2);
                    }
                }
                objects[j]->setR(objR); objects[j]->setC(objC);
            }
        /////////////////////////////////////Place some monsters///////////////////////////////////////
        others.clear();
            int numMons = randInt(2, 5 * (level + 1) + 1);
        
            for (int i = 0; i < numMons; i++)
            {
                int monR = randInt(1, MAXROWS-2);
                int monC = randInt(1, MAXCOLS-2);
                    
                while (playGround[monR][monC] == '#' || playGround[monR][monC] == '&' || playGround[monR][monC] == '>' || playGround[monR][monC] == '@' ||playGround[monR][monC] == ')'||playGround[monR][monC] == '?')
                {
                    monR = randInt(1, MAXROWS-2);
                    monC = randInt(1, MAXCOLS-2);
                };
        
               if (level < 2)
               {
                   int kind = randInt(1, 2);
                   switch (kind)
                   {
                   case 1:
                       others.push_back(new goblin(monR, monC));
                       break;
                   case 2:
                       others.push_back(new snake(monR, monC));
                       break;
                   }
               }
               else if (level < 3)
               {
                   int kind = randInt(1, 3);
                   switch (kind)
                   {
                   case 1:
                       others.push_back(new bogeymen(monR, monC));
                       break;
                   case 2:
                       others.push_back(new snake(monR, monC));
                       break;
                   case 3:
                       others.push_back(new goblin(monR, monC));
                       break;
                   }
               }
               else
               {
                   int kind = randInt(1, 4);
                   switch (kind)
                   {
                   case 1:
                       others.push_back(new bogeymen(monR, monC));
                       break;
                   case 2:
                       others.push_back(new snake(monR, monC));
                       break;
                   case 3:
                       others.push_back(new dragon(monR, monC));
                       break;
                   case 4:
                       others.push_back(new goblin(monR, monC));
                       break;
                   }
               }
                
            }
        ////////////////////////////////////Finish placing monsters/////////////////////////////////////
    }
}
Dungeon::~Dungeon()
{
    delete m_player; //destroy the new player pointer;
}

void Dungeon::setDisplay (bool value)
{
    isDisplay = value;
}
bool Dungeon::getDisplay () const
{
    return isDisplay;
}

int Dungeon::getLevel() const
{
    return level;
};

void Dungeon::display(string msg)
{
    clearScreen();
    for (int r = 0; r != MAXROWS; r++)
    {
        for (int c = 0; c != MAXCOLS; c++)
        {
            if (r == 0 || c == 0 || r == MAXROWS-1 || c == MAXCOLS-1)
                playGround[r][c] = '#'; //build the wall along the boundary;
        }
    }

    int playerR = m_player->getRow(); int playerC = m_player->getCol();
    if (level != MAXLEVEL)
    {
        if (playerR == stairRow && playerC == stairCol)
        {
            playGround[playerR][playerC] = '@';
        }
        else
        {
            playGround[playerR][playerC] = '@';
            playGround[stairRow][stairCol] = '>';
        }
    }
    else
    {
        if (playerR == idolRow && playerC == idolCol)
        {
            playGround[playerR][playerC] = '@';
        }
        else
        {
            playGround[playerR][playerC] = '@';
            playGround[idolRow][idolCol] = '&';
        }
    };

    //////////////////////////////////////Monster Dead, Drop Weapon/////////////////////////////////////
    if (getDrop() == true)
    {
        int dropR = getDeadMonR(); cout<<dropR<<endl;
        int dropC = getDeadMonC(); cout<<dropC<<endl;
        string monNM = getDeadMonNM();
        
        if (monNM == "Snakewoman")
        {
            if(playGround[dropR][dropC] == ' ')
            {
                if (trueWithProbability(1/3))
                {
                    objects.push_back((new weapon("magic fangs")));
                    objects[objects.size()-1]->setR(dropR);
                    objects[objects.size()-1]->setC(dropC);
                }
            }
        }
        
        if(monNM == "Goblin")
        {
            if(playGround[dropR][dropC] == ' ')
            {
                if (trueWithProbability(1/3))
                {
                    int choose = randInt(1, 2);
                    if (choose == 1)
                    {
                        objects.push_back((new weapon("magic fangs")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    }
                    if (choose == 2)
                    {
                        objects.push_back((new weapon("magic axes")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    }
                }
            }
        }
        if(monNM == "Dragon")
        {
            if(playGround[dropR][dropC] == ' ')
            {
                int kind = randInt(1, 5);
                switch (kind)
                {
                case 1:
                    objects.push_back((new scroll("scroll of strength")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    break;
                case 2:
                    objects.push_back((new scroll("scroll of enhance health")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    break;
                case 3:
                    objects.push_back((new scroll("scroll of enhance dexterity")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    break;
                case 4:
                    objects.push_back((new scroll("scroll of teleportation")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    break;
                case 5:
                    objects.push_back((new scroll("scroll of enhance armor")));
                        objects[objects.size()-1]->setR(dropR);
                        objects[objects.size()-1]->setC(dropC);
                    break;
                }
            }
        }
        
        if(monNM == "Bogeyman")
        {
            if(playGround[dropR][dropC] == ' ')
            {
                if (trueWithProbability(1/10))
                {
                    objects.push_back((new weapon("magic axes")));
                    objects[objects.size()-1]->setR(dropR);
                    objects[objects.size()-1]->setC(dropC);
                }
            }
        }
        setDrop(false);
    }
    
    //////////////////////////////////////Drop Weapon finished////////////////////////////////////////////////
 
    //////////////////////////////////////Drop some Weapons//////////////////////////////////////////////////
    for(int j = 0; j < objects.size();j++)
    {
        string name = objects[j]->getName();
        int r = objects[j]->getR();
        int c = objects[j]->getC();

            if (r == playerR && c == playerC)
            {
                playGround[r][c] = '@';
            }
            else
            {
                if(name == "mace"|| name == "short sword" ||  name == "long sword" ||name == "magic fangs"||name == "magic axes")
                {
                    playGround[r][c] = ')';
                }
                else
                {
                    playGround[r][c] = '?';
                }
            }
    }
    
     //////////////////////////////////////Drop  Weapons finished//////////////////////////////////////////////////

    
     //////////////////////////////////////Drop some Monsters on the map//////////////////////////////////////////////////
    for(int j = 0; j < others.size();j++)
    {
        string name = others[j]->getName();
        int r = others[j]->getRow();
        int c = others[j]->getCol();

        if(name == "Bogeyman")
        {
            playGround[r][c] = 'B';
        }
        else if (name == "Dragon")
        {
            playGround[r][c] = 'D';
        }
        else if (name == "Goblin")
        {
            playGround[r][c] = 'G';
        }
        else if (name == "Snakewoman")
        {
            playGround[r][c] = 'S';
        }
        else
        {
            playGround[r][c] = 'X';
        }
    }
    
     //////////////////////////////////////Finish Dropping some monsters//////////////////////////////////////////////////
    
    
    int tranR = randInt(1, MAXROWS-2);
    int tranC = randInt(1, MAXCOLS-2);
    if (m_player->getRead() == true && m_player->getScroll() == "scroll of teleportation")
    {
        while(playGround[tranR][tranC] != ' ')
        {
            tranR = randInt(1, MAXROWS-2);
            tranC = randInt(1, MAXCOLS-2);
        }
        playGround[tranR][tranC] = '@';
        m_player->setRow(tranR);
        m_player->setCol(tranC);
        playGround[playerR][playerC] = ' ';
    }
    
    for (int r = 0; r != MAXROWS; r++)
    {
        for (int c = 0; c != MAXCOLS; c++)
        {
            cout << playGround[r][c];
        }
        cout << endl;
    }

    if (m_player->getRead() == true && m_player->getScroll() == "scroll of teleportation")
    {
        playGround[tranR][tranC] = ' ';
    }
    else
    {
        playGround[playerR][playerC] = ' ';
    }
 
    cout<<"Dungeon Level: "<< level <<", Hit points: " <<m_player->getHit()<<", Armor: "<<m_player->getArmor()<<", Strength: " <<m_player->getStrength()<<", Dexterity: "<<m_player->getDexterity()<<endl<<endl;
    
    if (m_player->getWieldMove() == true)
    {
        cout<<"You are wielding "<<m_player->getWeapon()->getName()<<endl;
        m_player->setWieldMove(false);
    }
    if(isDisplay == true)
    {
        cout<<"You pick up "<<m_player->getTopInventory()<<endl;
        isDisplay = false;
    }
    
    if(isBagFull == true)
    {
        cout<<"Your knapsack is full; you can't pick that up."<<endl;
        isBagFull = false;
        isDisplay = false;
        m_player->setRead(false);
    }
    
    if(m_player->getRead() == true)
    {
        string name = m_player->getScroll();
        if(name != "scroll of enhance armor" && name != "scroll of strength" && name!= "scroll of enhance health" && name!= "scroll of enhance dexterity" && name != "scroll of teleportation")
        {
            cout<<"You can't read a "<<name<<endl;
            m_player->setRead(false);
        }
        else
        {
            cout<<"You read the scroll called "<<name<<endl;
            m_player->setRead(false);
        }
        if(name == "scroll of teleportation")
        {
            cout<<"You feel your body wrenched in space and time."<<endl;
        };
        if(name == "scroll of strength")
        {
            cout<<"Your muscles bulge."<<endl;
        };
        if(name == "scroll of enhance armor")
        {
            cout<<"Your armor glows blue."<<endl;
        };
        if(name == "scroll of enhance health")
        {
            cout<<"You feel your heart beating stronger."<<endl;
        };
        if(name == "scroll of enhance dexterity")
        {
            cout<<"You feel like less of a klutz."<<endl;
        };
        
  
    }

    if(getFight() == true) //if player fights monsters;
    {
        setFight(false);
        string motion;
        if (m_player->getWeapon()->getName() == "mace")
            motion = "swings";
        if (m_player->getWeapon()->getName() == "short sword")
        motion = "slashes";
        if (m_player->getWeapon()->getName() == "long sword")
        motion = "swings";
        if (m_player->getWeapon()->getName() == "magic fangs")
        motion = "strikes";
        if (m_player->getWeapon()->getName() == "magic axe")
        motion = "chops";
        
        bool sleep = false;
        
        string result;
        if (getisHit() == true)
        {
            if(getMonDead() == true)
            {
            result = " dealing a final blow.";
                setMonDead(false);
            }
            else if (getCurrentSt()>0 && m_player->getWeapon()->getName() == "magic fangs")
            {
//               cout<<"i sleep with time "<<getCurrentSt()<<endl;
                sleep = true;
                result = " and hits, putting ";
                setCurrentSt(0);
            }
            else
            result = " and hits.";
        }
        else
            result = " and misses.";
        
        if(sleep == false)
        cout<<"Player "<< motion<<" "<<m_player->getWeapon()->getName() <<" at the " << getaMon()->getName()<< result<<endl;
        else
        cout<<"Player "<< motion<<" "<<m_player->getWeapon()->getName() <<" at the " << getaMon()->getName()<< result<<getaMon()->getName() <<" to sleep."<<endl;
            
            
        
        setisHit(false); setFight(false);
    }
    
    if(getisBeat() == true) //if monster fights player;
    {
        for( vector<Actors*>::iterator p = badMon.begin(); p != badMon.end(); p++)
        {
            Actors* currentMon = *p;
            string motion;
            if (currentMon->getWeapon()->getName() == "mace")
                motion = "swings";
            if (currentMon->getWeapon()->getName() == "short sword")
            motion = "slashes";
            if (currentMon->getWeapon()->getName() == "long sword")
            motion = "swings";
            if (currentMon->getWeapon()->getName() == "magic fangs")
            motion = "strikes";
            if (currentMon->getWeapon()->getName() == "magic axes")
            motion = "chops";
            
            string result;
            bool sleep = false;
            if (getisHurt() == true)
            {
                if(m_player->getDead() == true)
                    result = " dealing a final blow.";
                else if(m_player->getSleep()>0)
                {
                    sleep = true;
                    result = " and hits, putting ";
                }
                else
                    result = " and hits.";
                
            }
            else
                result = " and misses.";
            
            if (sleep == false)
            cout<<"the "<< currentMon->getName() <<" "<<motion<<" "<<currentMon->getWeapon()->getName() <<" at Player" << result<<endl;
            else
            cout<<"the "<< currentMon->getName() <<" "<<motion<<" "<<currentMon->getWeapon()->getName() <<" at Player" << result<<" Player to sleep." <<endl;
            
            
            badMon.erase(p);
            p--;
        }
        setisBeat(false);
        setisHurt(false);
    }
}

void Dungeon::set(int r, int c, char x)
{
    playGround[r][c] = x;
}

char Dungeon::get(int r, int c) const
{
    return playGround[r][c];
}

player* Dungeon::getplayer() const
{
    return m_player;
}

Objects* Dungeon::getObject(int pos)
{
    return this->objects[pos];
}

int Dungeon::numObjects()
{
    return m_size;
}

void Dungeon::removeObject(Objects* pos)
{
    Objects* rmv = pos;
    for( vector<Objects*>::iterator p = objects.begin(); p != objects.end(); p++)
    {
        if(*p == rmv)
        {
            objects.erase(p);
            break;
        }
    }
}

size_t Dungeon::currentObjSize()
{
    return objects.size();
}

bool Dungeon::fight(Actors* A, Actors* a) //fight functions;
{
    int damage;
    bool fight = true; 
    bool hit = false;

    if (A->getName() == "player") //if the player is the attacker;
    {
        if (A->getWeapon()->getName() != "magic fangs") //not using magic fangs;
            {
                if (A != nullptr && a != nullptr)
                        {
                            if (A->getDead() == false && a->getDead() == false)
                            {
                                int attack = A->getDexterity() + A->getWeapon()->getBonus();
                                int defend = a->getDexterity() + a->getDexterity();
                    
                                if (randInt(1, attack) >= randInt(1, defend))
                                {
                                    damage = randInt(0, A->getStrength() + A->getWeapon()->getDamage() - 1);
                                    a->setHit((a->getHit()-damage));
                                    hit = true; setisHit(true);
                                    setisHurt(true);
                                }
                            }
                        }
            }
            else //use magic fangs;
            {
                if (A != nullptr && a != nullptr)
                        {
                            if (A->getDead() == false && a->getDead() == false)
                            {
                                int attack = A->getDexterity() + A->getWeapon()->getBonus();
                                int defend = a->getDexterity() + a->getDexterity();
                    
                                if (randInt(1, attack) >= randInt(1, defend))
                                {
                                    damage = randInt(0, A->getStrength() + A->getWeapon()->getDamage() - 1);
                                    a->setHit((a->getHit()-damage));
                                    hit = true; setisHit(true);
                                    setisHurt(true);
                                }
                                if(trueWithProbability(0.2)) //sleep;
                                {
                                    int X = randInt(2, 6);
                                    if (a->getSleep() < X)
                                    {
                                        a->setSleep(X);
                                    }
                                        setCurrentSt(a->getSleep());
                                }
                            }
                        }
            }
    }
    else //monster fights player;
    {
        if (A->getWeapon()->getName() != "magic fangs")
            {
                if (A != nullptr && a != nullptr)
                        {
                            if (A->getDead() == false && a->getDead() == false)
                            {
                //                fight = true; setFight(true);
                                int attack = A->getDexterity() + A->getWeapon()->getBonus();
                                int defend = a->getDexterity() + a->getDexterity();
                    
                                if (randInt(1, attack) >= randInt(1, defend))
                                {
                                    damage = randInt(0, A->getStrength() + A->getWeapon()->getDamage() - 1);
                                    a->setHit((a->getHit()-damage));
                                    hit = true; setisHit(true);
                                    setisHurt(true);
                                }
                            }
                        }
            }
            else
            {
                if (A != nullptr && a != nullptr)
                        {
                            if (A->getDead() == false && a->getDead() == false)
                            {
                                int attack = A->getDexterity() + A->getWeapon()->getBonus();
                                int defend = a->getDexterity() + a->getDexterity();
                    
                                if (randInt(1, attack) >= randInt(1, defend))
                                {
                                    damage = randInt(0, A->getStrength() + A->getWeapon()->getDamage() - 1);
                                    a->setHit((a->getHit()-damage));
                                    hit = true; setisHit(true);
                                    setisHurt(true);
                                }
                                if(trueWithProbability(0.2)) //sleep;
                                {
                                    int X = randInt(2, 6);
                                    if (a->getSleep() < X)
                                    {
                                        a->setSleep(X);
                                    }
                                }
                            }
                        }
            }
    };
    return fight;
}

Actors* Dungeon::getOthers(int r, int c) const //get the monster at that specific position;
{
    for (int i = 0; i != others.size(); i++)
    {
        int monR = others[i]->getRow();
        int monC = others[i]->getCol();
        if (monR == r && monC == c)
        {
            return others[i];
            break;
        }
    }
    return nullptr;
};

void Dungeon::setFight (bool value)
{
    isFight = value;
};
bool Dungeon::getFight () const
{
    return isFight;
};

void Dungeon::setaMon (Actors* a)
{
    aMon = a;
}
Actors* Dungeon::getaMon () const
{
    return aMon;
}

void Dungeon::setisHit (bool value)
{
    isHit = value;
}
bool Dungeon::getisHit () const
{
    return isHit;
}

bool Dungeon::checkDeath(Actors* b) //check if the player/monster is dead;
{

    if (b->getHit() <= 0)
    {
        playGround[b->getRow()][b->getCol()] = ' ';
        for( vector<Actors*>::iterator p = others.begin(); p != others.end(); p++)
        {
            if(*p == b)
            {
                others.erase(p);
                break;
            }
        }
        return true;
    }
    return false;
};

void Dungeon::setDrop (bool value)
{
    dropItem = value;
}
bool Dungeon::getDrop () const
{
    return dropItem;
}

int Dungeon::getDeadMonR ()const
{
    return deadMonR;
}

int Dungeon::getDeadMonC ()const
{
    return deadMonC;
}

void Dungeon::setDeadMon (int row, int col)
{
    deadMonR = row;
    deadMonC = col;
}

void Dungeon::setDeadMonNM (string nm)
{
    deadMonNM = nm;
}
string Dungeon::getDeadMonNM () const
{
    return deadMonNM;
}

string Dungeon::monstermove() //monster take its action;
{
    for (int i = 0; i < others.size(); i++)
    {
        Actors* mon = others[i];
        if(mon->getSleep()>0)
        {
            mon->setSleep(mon->getSleep()-1);
            currentMonSleepTime--;
        }
        else
        {
                    int mr = mon->getRow();
                    int mc = mon->getCol();
                    int beforeR = mr; int beforeC = mc;
                    int pr = m_player->getRow();
                    int pc = m_player->getCol();
                    
                    string mName = mon->getName();
                    char sym = ' ';
                    if (mName == "Bogeyman")
                        sym = 'B';
                    if (mName == "Dragon")
                        sym = 'D';
                    if (mName == "Goblin")
                        sym = 'G';
                    if (mName == "Snakewoman")
                        sym = 'S';

            //check if the player is around;
                    if ( (((mr+1)==pr)  &&  (mc==pc))  ||  (((mr-1)==pr)  &&  (mc==pc))  || (((mr)==pr)  &&  ((mc+1)==pc))  ||(((mr)==pr)  &&  (mc-1==pc))   )
                    {
                        setisBeat(true);

                            badMon.push_back(mon);

                                    fight(mon, m_player);
                                    if(m_player->getHit()<=0)
                                    {
                                        m_player->setHit(0);
                                        m_player->setDead();
                                        m_player->Actors::setDead(true);
                                        return "";
                                    }

                    }
                    
                    switch (sym)
                    {
                            
                        
                    case 'D': //a dragon doesn't move
                    {
                        if (trueWithProbability(0.1))
                            mon->setHit(mon->getHit() + 1); //dragon can regain hitpoint;
                        break;
                    }
                    case 'B':
                    {
                        if (abs(mr - pr) + abs(mc - pc) <= 5)
                        {
                            if(abs(mr - pr)<=abs(mc - pc)) //row dis closer or equal;
                            {
                                if(abs(mr - pr) != 0)
                                {
                                    if(mr < pr)
                                        mr++;
                                    else if (mr > pr)
                                        mr--;
                                }else
                                {
                                    if(mc < pc)
                                        mc++;
                                    else if (mc > pc)
                                        mc--;
                                }
                                
                            }
                            else //col dis closer;
                            {
                                if(abs(mc - pc) != 0)
                                {
                                    if(mc < pc)
                                        mc++;
                                    else if (mc > pc)
                                        mc--;
                                }else
                                {
                                    if(mr < pr)
                                        mr++;
                                    else if (mr > pr)
                                        mr--;
                                }
                            }
                            if (playGround[mr][mc] == ')' || playGround[mr][mc] == '?' || playGround[mr][mc] == ' ' || playGround[mr][mc] == '&' || playGround[mr][mc] == '>' )
                            {
                                if((mr == pr && mc == pc) == false)
                                {
                                    mon->setRow(mr);
                                    mon->setCol(mc);
                                    playGround[beforeR][beforeC] = ' ';
                                }
                            }
                            //try to move around the wall or other objects;
                            if(playGround[mr][mc] == '#'||playGround[mr][mc] == 'D'||playGround[mr][mc] == 'B'||playGround[mr][mc] == 'S'||playGround[mr][mc] == 'G')
                            {
                                    int dis = abs(beforeR - pr) + abs(beforeC - pc);
                                    char up = playGround[beforeR-1][beforeC];
                                    char down = playGround[beforeR+1][beforeC];
                                    char left = playGround[beforeR][beforeC-1];
                                    char right = playGround[beforeR][beforeC+1];
                                    if (up != '#' && up != 'B' && up != 'D'&& up != 'S'&& up != 'G'&& abs((beforeR-1)-pr)+abs(beforeC-pc) < dis )
                                    {
                                        mon->setRow(beforeR-1);
                                        mon->setCol(beforeC);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (down != '#' && down != 'B' && down != 'D'&& down != 'S'&& down != 'G' && abs((beforeR+1)-pr)+abs(beforeC-pc) < dis )
                                    {
                                        mon->setRow(beforeR+1);
                                        mon->setCol(beforeC);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (left != '#' && left != 'B' && left != 'D'&& left != 'S'&& left != 'G' && abs((beforeR)-pr)+abs((beforeC-1)-pc) < dis )
                                    {
                                        mon->setRow(beforeR);
                                        mon->setCol(beforeC-1);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (right != '#' && right != 'B' && right != 'D'&& right != 'S'&& right != 'G' && abs((beforeR)-pr)+abs((beforeC+1)-pc) < dis )
                                    {
                                        mon->setRow(beforeR);
                                        mon->setCol(beforeC+1);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                            }
                        }
                        
                        break;
                    }
                    case 'S':
                    {
                        if (abs(mr - pr) + abs(mc - pc) <= 3)
                        {
                            if(abs(mr - pr)<=abs(mc - pc)) //row dis closer or equal;
                            {
                                if(abs(mr - pr) != 0)
                                {
                                    if(mr < pr)
                                        mr++;
                                    else if (mr > pr)
                                        mr--;
                                }else
                                {
                                    if(mc < pc)
                                        mc++;
                                    else if (mc > pc)
                                        mc--;
                                }
                                
                            }
                            else //col dis closer;
                            {
                                if(abs(mc - pc) != 0)
                                {
                                    if(mc < pc)
                                        mc++;
                                    else if (mc > pc)
                                        mc--;
                                }else
                                {
                                    if(mr < pr)
                                        mr++;
                                    else if (mr > pr)
                                        mr--;
                                }
                                
                            }
                            if (playGround[mr][mc] == ')' || playGround[mr][mc] == '?' || playGround[mr][mc] == ' ' || playGround[mr][mc] == '&' || playGround[mr][mc] == '>')
                            {
                                if((mr == pr && mc == pc) == false)
                                {
                                    mon->setRow(mr);
                                    mon->setCol(mc);
                                    playGround[beforeR][beforeC] = ' ';
                                }
                            }
                            //try to move around the wall or other objects;
                            if(playGround[mr][mc] == '#'||playGround[mr][mc] == 'D'||playGround[mr][mc] == 'B'||playGround[mr][mc] == 'S'||playGround[mr][mc] == 'G')
                            {

                                    int dis = abs(beforeR - pr) + abs(beforeC - pc);
                                    char up = playGround[beforeR-1][beforeC];
                                    char down = playGround[beforeR+1][beforeC];
                                    char left = playGround[beforeR][beforeC-1];
                                    char right = playGround[beforeR][beforeC+1];
                                    if (up != '#' && up != 'B' && up != 'D'&& up != 'S'&& up != 'G'&& abs((beforeR-1)-pr)+abs(beforeC-pc) < dis )
                                    {
                                        mon->setRow(beforeR-1);
                                        mon->setCol(beforeC);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (down != '#' && down != 'B' && down != 'D'&& down != 'S'&& down != 'G' && abs((beforeR+1)-pr)+abs(beforeC-pc) < dis )
                                    {
                                        mon->setRow(beforeR+1);
                                        mon->setCol(beforeC);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (left != '#' && left != 'B' && left != 'D'&& left != 'S'&& left != 'G' && abs((beforeR)-pr)+abs((beforeC-1)-pc) < dis )
                                    {
                                        mon->setRow(beforeR);
                                        mon->setCol(beforeC-1);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                                    else if (right != '#' && right != 'B' && right != 'D'&& right != 'S'&& right != 'G' && abs((beforeR)-pr)+abs((beforeC+1)-pc) < dis )
                                    {
                                        mon->setRow(beforeR);
                                        mon->setCol(beforeC+1);
                                        playGround[beforeR][beforeC] = ' ';
                                    }
                            }
                        }

                        break;
                    }
                    case 'G':
                    {
                        //Goblins are very intelligent creatures, and can smell the player if
                        //the player is reachable in 15 steps or less.
                        {
                                    if (abs(mr - pr) + abs(mc - pc) <= 15)
                                    {
                                        if(abs(mr - pr)<=abs(mc - pc)) //row dis closer or equal;
                                        {
                                            if(abs(mr - pr) != 0)
                                            {
                                                if(mr < pr)
                                                    mr++;
                                                else if (mr > pr)
                                                    mr--;
                                            }else
                                            {
                                                if(mc < pc)
                                                    mc++;
                                                else if (mc > pc)
                                                    mc--;
                                            }
                                            
                                        }
                                        else //col dis closer;
                                        {
                                            if(abs(mc - pc) != 0)
                                            {
                                                if(mc < pc)
                                                    mc++;
                                                else if (mc > pc)
                                                    mc--;
                                            }else
                                            {
                                                if(mr < pr)
                                                    mr++;
                                                else if (mr > pr)
                                                    mr--;
                                            }
                                            
                                        }
                                        if (playGround[mr][mc] == ')' || playGround[mr][mc] == '?' || playGround[mr][mc] == ' ' || playGround[mr][mc] == '&' || playGround[mr][mc] == '>')
                                        {
                                            if((mr == pr && mc == pc) == false)
                                            {
                                                mon->setRow(mr);
                                                mon->setCol(mc);
                                                playGround[beforeR][beforeC] = ' ';
                                            }
                                        }
                                        if(playGround[mr][mc] == '#'||playGround[mr][mc] == 'D'||playGround[mr][mc] == 'B'||playGround[mr][mc] == 'S'||playGround[mr][mc] == 'G')
                                        {

                                                int dis = abs(beforeR - pr) + abs(beforeC - pc);
                                                char up = playGround[beforeR-1][beforeC];
                                                char down = playGround[beforeR+1][beforeC];
                                                char left = playGround[beforeR][beforeC-1];
                                                char right = playGround[beforeR][beforeC+1];
                                                if (up != '#' && up != 'B' && up != 'D'&& up != 'S'&& up != 'G'&& abs((beforeR-1)-pr)+abs(beforeC-pc) < dis )
                                                {
                                                    mon->setRow(beforeR-1);
                                                    mon->setCol(beforeC);
                                                    playGround[beforeR][beforeC] = ' ';
                                                }
                                                else if (down != '#' && down != 'B' && down != 'D'&& down != 'S'&& down != 'G' && abs((beforeR+1)-pr)+abs(beforeC-pc) < dis )
                                                {
                                                    mon->setRow(beforeR+1);
                                                    mon->setCol(beforeC);
                                                    playGround[beforeR][beforeC] = ' ';
                                                }
                                                else if (left != '#' && left != 'B' && left != 'D'&& left != 'S'&& left != 'G' && abs((beforeR)-pr)+abs((beforeC-1)-pc) < dis )
                                                {
                                                    mon->setRow(beforeR);
                                                    mon->setCol(beforeC-1);
                                                    playGround[beforeR][beforeC] = ' ';
                                                }
                                                else if (right != '#' && right != 'B' && right != 'D'&& right != 'S'&& right != 'G' && abs((beforeR)-pr)+abs((beforeC+1)-pc) < dis )
                                                {
                                                    mon->setRow(beforeR);
                                                    mon->setCol(beforeC+1);
                                                    playGround[beforeR][beforeC] = ' ';
                                                }
                                        }
                                    }

                                    break;
                                }
                        

                    }
                    }
        }
    }
    return "";
}

void Dungeon::setisBeat (bool value)
{
    isBeat = value;
};

bool Dungeon::getisBeat () const
{
    return isBeat;
};

void Dungeon::setisHurt (bool value)
{
    isHurt = value;
}

bool Dungeon::getisHurt () const
{
    return isHurt;
}

void Dungeon::setPlayerNext (int r, int c)
{
    playerNextR = r;
    playerNextC = c;
}
int Dungeon::getPlayerNextR () const
{
    return playerNextR;
}
int Dungeon::getPlayerNextC () const
{
    return playerNextC;
}

void Dungeon::setMonDead (bool value)
{
    isMonDead = value;
}
bool Dungeon::getMonDead () const
{
    return isMonDead;
}

int Dungeon::getIdolR () const
{
    return idolRow;
};

int Dungeon::getIdolC () const
{
    return idolCol;
};

int Dungeon::getCurrentSt () const
{
    return currentMonSleepTime;
}
void Dungeon::setCurrentSt (int a)
{
    currentMonSleepTime = a;
}

void Dungeon::setBagFull (bool value)
{
    isBagFull = value;
}
bool Dungeon:: getBagFull () const
{
    return isBagFull;
}
