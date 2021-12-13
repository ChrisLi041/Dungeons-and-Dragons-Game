//
//  Actors.hpp
//  CS32 Project 3
//
//  Created by Siyuan Li on 5/15/20.
//  Copyright © 2020 Siyuan Li. All rights reserved.
#ifndef Actors_h
#define Actors_h
#include "Objects.h"
#include <vector>
#include "utilities.h"
#include <string>
#include <iostream>
using namespace std;

class Dungeon;

class Actors {
public:
    Actors(int r, int c, int hit, string wp, int ar, int st, int dt, int slp);
    Actors(int r, int c);
    virtual ~Actors();
    virtual void move(char dir);//only for players;
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
    void monchangeWeapon(weapon w);
    string fight(Actors &enmy);
    string pickup(Objects &obj);
    Objects* getWeapon() const;
    void setWeapon(Objects* current);
    void setArmor (int pt);
    void setStrength (int pt);
    void setDexterity (int pt);
    void setMaxHit (int pt);
    void setHit (int pt);
    void setSleep (int pt);
    int getArmor () const;
    int getStrength () const;
    int getDexterity () const;
    int getMaxHit () const;
    int getHit () const;
    int getSleep() const;
    void setName (string nm);
    string getName () const;
    void setDead(bool value);
    bool getDead() const;
    void setPushed (bool value);
    bool getPushed () const;
private:
    int r; //the actor's current row;
    int c; //the actor's current column;
    int hit; //hit;
    int maxHit;
    int armor; //armor;
    int strength; //strength;
    int dexterity; //dexterity ponits
    int sleepTime;//sleep time
    Objects* m_weapon;
//    scroll m_scrool;
    string monName;
    bool isDead;
    bool isPushed;
    
};

class player : public Actors
{
public:
    player(int r, int c);
    player(const player& other); //copy constructor;
    virtual void move(const char input) ;
    virtual void setWin(); virtual bool getWin() const;
    virtual void setDead(); virtual bool getDead() const;
    size_t getInventorySize();
    void addObject(Objects* add);
    void showInventory();
    void wieldWeapon(char input);
    void readScroll(char input);
    bool getWieldMove() const;
    void setWieldMove(bool value);
    string getTopInventory() const;
    void setRead (bool value);
    bool getRead () const;
    string getScroll () const;
    void setScroll (string n);
private:
    bool Win;
    bool Dead;
    vector<Objects*> m_inventory;
    size_t inventorySize;
    bool wieldMove;
    int weaponSize;
    bool readable;
    string currentScroll;
};

class bogeymen : public Actors
{
public:
    bogeymen(int r, int c);
};

class goblin : public Actors
{
public:
    goblin(int r, int c);
};
class dragon : public Actors
{
public:
    dragon(int r, int c);
    void sethp(int bonus);
private:
    int maxhp;
};

class snake : public Actors
{
public:
    snake(int r, int c);
};

#endif
