// Game.h

#ifndef Game_h
#define Game_h
#include "globals.h"
#include "Dungeon.h"
#include "utilities.h"
#include "Objects.h"
#include "Actors.h"
#include <vector>

// You may add data members and other member functions to this class.

class Game
{
public:
    string go(); //player take action;
    Game(int goblinSmellDistance); //game constructor;
    void play(); //play function;
    void descend(); //descend function;
    bool pickObject(); //pick up the object;
    bool getdescondMove() const;
    void setdescondMove (bool value);
    bool getgetObject() const;
    void setgetObject (bool value);
    bool getDont() const;
    void setDont (bool value);
    void setQuit (bool value);
    bool getQuit () const;
private:
    Dungeon* m_dungeon; //pointer to current dungeon;
    player* m_player; //pointer to current player;
    bool descendMove;
    bool dontGetChar;
    bool getObject;
    bool isQuit;
    
};
#endif // Game_h
