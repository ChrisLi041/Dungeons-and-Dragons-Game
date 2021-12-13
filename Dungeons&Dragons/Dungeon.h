//
//  Dungeon.hpp
//  CS32 Project 3
//
//  Created by Siyuan Li on 5/15/20.
//  Copyright © 2020 Siyuan Li. All rights reserved.
//
#ifndef Dungeon_h
#define Dungeon_h
#include "globals.h"
#include "utilities.h"
#include "Actors.h"
#include "Objects.h"
#include <vector>
#include <string>
class Actors;
class player;
class Dungeon
{
public:
    Dungeon(int l,player* p);
    ~Dungeon();
    int getLevel() const;
    void display(string msg);
    void set(int x, int y, char c);
    char get(int x, int y) const;
    player* getplayer() const;
    Objects* getObject(int pos);
    int numObjects();
    size_t currentObjSize();
    void removeObject(Objects* pos);
    void setDisplay (bool value);
    bool getDisplay () const;
    bool fight(Actors* A, Actors* a);
    Actors* getOthers(int r, int c) const;
    void setFight (bool value);
    bool getFight () const;
    void setaMon (Actors* a);
    Actors* getaMon () const;
    void setisHit (bool value);
    bool getisHit () const;
    bool checkDeath(Actors* b);
    void setDrop (bool value);
    bool getDrop () const;
    void setDeadMon (int row, int col);
    int getDeadMonR ()const;
    int getDeadMonC ()const;
    void setDeadMonNM (string nm);
    string getDeadMonNM () const;
    string monstermove();
    void setisBeat (bool value);
    bool getisBeat () const;
    void setisHurt (bool value);
    bool getisHurt () const;
    void setPlayerNext (int r, int c);
    int getPlayerNextR () const;
    int getPlayerNextC () const;
    void setMonDead (bool value);
    bool getMonDead () const;
    int getIdolR () const;
    int getIdolC () const;
    int getCurrentSt () const;
    void setCurrentSt (int a);
    void setBagFull (bool value);
    bool getBagFull () const;
//    void setSmell (int s);
//    int getSmell () const;
private:
    char playGround[MAXROWS][MAXCOLS];
    int stairRow; int stairCol;
    int idolRow; int idolCol;
    int m_box;
    int m_size;
    int level;
    vector<Objects*> objects;
    vector<Actors*> others;
    player* m_player;
    struct center
    {
        int centerRow;
        int centerCol;
    };
    bool isDisplay;
    bool isFight;
    Actors* aMon;
    bool isHit;
    bool dropItem;
    int deadMonR;
    int deadMonC;
    string deadMonNM;
    bool isBeat;
    bool isHurt;
    vector<Actors*> badMon;
    int playerNextR;
    int playerNextC;
    bool isMonDead; //check if the monster that the player fights dies;
    int currentMonSleepTime;
    bool isBagFull;
//    int smell;
};

#endif //Dungeon_h
