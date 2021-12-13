//
//  Actors.cpp
//  CS32 Project 3
//
//  Created by Siyuan Li on 5/15/20.
//  Copyright © 2020 Siyuan Li. All rights reserved.

#include "Actors.h"
#include "utilities.h"
#include <iostream>
using namespace std;

class Game;

Actors::Actors(int r, int c, int hit, string wp, int ar, int st, int dt, int slp)
    :r(r), c(c), hit(hit), armor(ar),strength(st),dexterity(dt), sleepTime(slp)
{
    m_weapon =  new weapon(wp);
    maxHit = 20;
    setDead(false);
}

Actors::Actors(int r, int c)
:r(r), c(c), hit(0), armor(0),strength(0),dexterity(0), sleepTime(0)
{
    m_weapon = new weapon("short sword");
    maxHit = 20;
    setDead(false);
}

Actors::~Actors()
{}

void Actors::setDead(bool value)
{
    isDead = value;
}

bool Actors::getDead() const
{
    return isDead;
}


void Actors:: move(char dir)
{
    
};

void Actors::setName (string nm)
{
    monName = nm;
}
string Actors::getName () const
{
    return monName;
}

//void Actors:: monchangeWeapon(weapon w)
//{
//     = w;
//}
void Actors::setRow(int row)
{
    r = row;
}

void Actors::setCol(int col)
{
    c = col;
}

//string Actors::fight(Actors& enmy)
//{
//    //fighting
//    //modify enmy and self status
//    return "fighting";
//
//}
//
//string Actors::pickup(Objects &obj)
//{
//    //change inventory
//    return "pick up sth";
//    //pick up weapon or scroll
//}

player::player(int r, int c)
    : Actors(r, c, 20, "short sword", 2, 2, 2, 0), Win(false), Dead(false)
{
    m_inventory.push_back(new weapon("short sword"));
    inventorySize = 1;
    setWieldMove(false);
    weaponSize = 1;
    setRead(false);
    setName("player");
    Actors::setDead(false);
};

player::player(const player& other)
    : Actors(other.getRow(),other.getCol(),other.getHit(), other.getWeapon()->getName(),other.getArmor(),other.getStrength(),other.getDexterity(),other.getSleep()), Win(false), Dead(false)
{
    this->inventorySize = other.inventorySize;
    setWieldMove(false);
    this->weaponSize = other.weaponSize;
    this->m_inventory = other.m_inventory;
    setRead(false);
    Actors::setDead(false);
    this->setName("player");
    

}

bool player::getWieldMove() const
{
    return wieldMove;
}
void player::setWieldMove(bool value)
{
    wieldMove = value;
}

void player::move(const char input)
{
    int row = this->getRow();
    int col = this->getCol();
    switch (input)
    {
        case ARROW_UP:
            setRow(row - 1);
            break;
        case ARROW_RIGHT:
            setCol(col + 1);
            break;
        case ARROW_DOWN:
            setRow(row + 1);
            break;
        case ARROW_LEFT:
            setCol(col - 1);
            break;
    };
}

size_t player::getInventorySize()
{
    return m_inventory.size();
}

string player::getTopInventory() const
{
    return m_inventory[m_inventory.size()-1]->getName();
}

void player::addObject(Objects* newObj)
{
    Objects* newAdd = newObj;
    m_inventory.push_back(newAdd);
}

void player::setWin()
{
    Win = true;
}

bool player::getWin() const
{
    return Win;
}

void player::setDead()
{
    Dead = true;
}

bool player::getDead() const
{
    return Dead;
}


int Actors::getCol() const
{
    return c;
}

int Actors::getRow() const
{
    return r;
}

 void player::showInventory()
{
    for(int i = 0; i != m_inventory.size(); i++)
        {
            cout<< char(i+97) <<". " << m_inventory[i]->getName()<<endl; //cout all the inverntory items;
        }
}

Objects* Actors::getWeapon() const
{
    return m_weapon;
}

void Actors::setWeapon(Objects* current)
{
    m_weapon = current;
}

void Actors::setArmor( int pt)
{
    armor = pt;
}
void Actors::setStrength(int pt)
{
    strength = pt;
}
void Actors::setDexterity(int pt)
{
    dexterity = pt;
}
void Actors::setMaxHit(int pt)
{
    maxHit = pt;
}
int Actors::getArmor() const
{
    return armor;
}
int Actors::getStrength() const
{
    return strength;
}
int Actors::getDexterity() const
{
    return dexterity;
}
int Actors::getMaxHit() const
{
    return maxHit;
}
void Actors::setHit(int pt)
{
    hit = pt;
}
int Actors::getHit() const
{
    return hit;
}

void Actors::setSleep(int pt)
{
    sleepTime = pt;
}
int Actors::getSleep() const
{
    return sleepTime;
}

void player::wieldWeapon(char input)
{
    size_t size = m_inventory.size();
    int choice = char(input - 97);//a == 0; b == 1; c==2;...
    if (choice < size && choice >= 0)
    {

        string name = m_inventory[choice]->getName();

        
        if ( (name !="mace" && name != "short sword"&& name !="long sword" && name != "magic axes" && name!= "magic fangs"))
            {
                setWieldMove(false);
            }
            else
            {
                setWeapon(m_inventory[choice]);
        
                setWieldMove(true);
                
            }
        
    }

    
    
}

string player::getScroll () const
{
    return currentScroll;
}
void player::setScroll (string n)
{
    currentScroll = n;
}

void player::readScroll(char input)
{
    size_t size = m_inventory.size();
    int choice = char(input - 97); // input to inventory position
    //postion to particular object
    if( choice >= 0 && choice < size)
       
////       || (name != "scroll of improve armor" && name != "scroll of raise strength" && name!= "scroll of enhance health"&& name!= "scroll of enhance dexterity"&& name != "scroll of teloeportation") )
//
//    {
////        cout<<"you are not selecting a scroll or you enter an invalid letter"<<endl;
//    }
//    else//self-destructed
    {
        string name = m_inventory[choice]->getName();
        if(name != "scroll of enhance armor" && name != "scroll of strength" && name!= "scroll of enhance health" && name!= "scroll of enhance dexterity" && name != "scroll of teleportation")
        {
            setRead(true);
            setScroll(name);
        }
        else
        {
            setRead(true);
            setScroll(name);
            Objects* dump= m_inventory[choice];
            for( vector<Objects*>::iterator p = m_inventory.begin(); p != m_inventory.end();p++)
            {
                if(*p == dump)
                {
                    p = m_inventory.erase(p);
                    p--;
                    break;
                }
            }
            if(name == "scroll of teleportation")
            {
//                int playerR = randInt(1, MAXROWS-2);
//                int playerC = randInt(1, MAXCOLS-2);
//                // !! check if step on wall/monster
//                setRow(moveR);
//                setCol(moveL);
//                cout<<" you read a scroll of teleportation and you are randomly placed"<<endl;
            }
            else if (name == "scroll of enhance armor")
            {
                int improve = randInt(1, 3);
                setArmor(getArmor()+improve);
                if(getArmor() > 99)
                {
                    setArmor(99);
                }
//                cout<<"you read scroll of improve armor and your armor pt increase to "<<getArmor()<<endl;
            }
            else if (name == "scroll of strength")
            {
                int raise = randInt(1, 3);
                setStrength(getStrength()+raise);
                if(getStrength() > 99)
                {
                    setStrength(99);
                }
//                cout<<"you read scroll of raise strength and your strength pt increase to "<<getStrength()<<endl;
            }
            else if (name == "scroll of enhance health")
            {
                int enhance = randInt(3, 8);
                setMaxHit(20+enhance);
                if(getMaxHit() > 99)
                {
                    setMaxHit(99);
                }
//                cout<<"you read scroll of enhance health and your max hit pt increase to "<<getMaxHit()<<endl;
            }
            else
            {
                setDexterity(getDexterity()+1);
                if(getDexterity() > 99)
                {
                    setDexterity(99);
                }
//                cout<<"you read scroll of enhance dexterity and your dexterity pt increase to "<<getDexterity()<<endl;
            }
        }
        
    }
    //object to particular effect
    
}

void player::setRead (bool value)
{
    readable =  value;
}
bool player::getRead () const
{
    return readable;
}

bogeymen::bogeymen(int r, int c)
    : Actors(r, c, randInt(5, 10), "short sword", 2, randInt(2, 3), randInt(2, 3), 0)
{
    setName("Bogeyman");
    setDead(false);
    setMaxHit(getHit());
    setPushed(false);
}

goblin::goblin(int r, int c)
    : Actors(r, c, randInt(15, 20), "short sword", 1, 3, 1, 0)
{
    setName("Goblin");
    setDead(false);
    setMaxHit(getHit());
    setPushed(false);
}

dragon::dragon(int r, int c)
    : Actors(r, c, randInt(20, 25),"long sword", 4, 4, 4, 0)
{
    setName("Dragon");
    setDead(false);
    setMaxHit(getHit());
    setPushed(false);
}
snake::snake(int r, int c)
    : Actors(r, c, randInt(3, 6), "magic fangs", 1, 3, 1, 0)
{
    setName("Snakewoman");
    setDead(false);
    setMaxHit(getHit());
    setPushed(false);
}

void Actors:: setPushed (bool value)
{
    isPushed = value;
}
bool Actors:: getPushed () const
{
    return isPushed;
}
