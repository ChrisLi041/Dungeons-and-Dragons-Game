// Game.cpp

#include "Game.h"
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    //generate a new dungeon
    m_dungeon = new Dungeon(0,nullptr);
    m_player = m_dungeon->getplayer();
//    m_dungeon->setSmell(goblinSmellDistance);
    //set all the boolean statment to false as initialization;
    descendMove = false;
    getObject = false;
    setQuit(false);
    setgetObject(false);
    m_dungeon->setFight(false);
    m_dungeon->setisHit(false);
    m_dungeon->setDisplay(false);
    m_dungeon->setDrop(false);
    m_dungeon->setMonDead(false);
    m_dungeon->setCurrentSt(0);
    m_dungeon->setBagFull(false);
}

bool Game::getdescondMove() const //check if descend option is available;
{
    return descendMove;
};

void Game::setdescondMove(bool value)
{
    descendMove = value;
};

bool Game::getDont() const //check if for the next round the user need to type a char;
{
    return dontGetChar;
};

void Game::setDont(bool value)
{
    dontGetChar = value;
};

bool Game::getgetObject() const //check if a object can be picked up;
{
    return getObject;
};

void Game::setgetObject(bool value) //set a status to be yes/no pickable;
{
    getObject = value;
};




string Game::go()
{

    for (;;) //keep prompting;
    {
        char input;
        if (dontGetChar == false)
        {
            input = getCharacter(); //get a input from the user;
        }
        else
        {
            input = ' '; //deault input when a input is not needed;
            dontGetChar = false;
        }
        
        m_player = m_dungeon->getplayer(); //get the player from the dungeon;
        
        if (m_player == nullptr) //check if the player is valid;
            exit(1);
        else if(m_player->getSleep()>0) //check if the player is sleeping;
        {
            m_player->setSleep(m_player->getSleep()-1);
            return "";
        }
        else
        {
            if (trueWithProbability(0.1)) //player may gain some hitpoint;
            {
                m_player->setHit(m_player->getHit()+1);
                if (m_player->getHit()>m_player->getMaxHit())
                {
                    m_player->setHit(m_player->getMaxHit());
                }
            }
            
            int currentPlayerR = m_player->getRow();
            int currentPlayerC = m_player->getCol();
            char nextPos;
            input = tolower(input); //make cap or lower letter all valid;
            switch (input)
            {
                case ARROW_UP: //move up;
//                case 'K':
                        nextPos = m_dungeon->get(currentPlayerR - 1, currentPlayerC);
                        if (currentPlayerR <= 1 || nextPos == '#') //check if valid;
                            return "";
                        else
                            currentPlayerR--; //move;
                        break;
                case ARROW_RIGHT: //move right;
//                case 'L':
                        nextPos = m_dungeon->get(currentPlayerR, currentPlayerC + 1);
                        if (currentPlayerC >= MAXCOLS - 2 || nextPos == '#') //check if valid;
                            return "";
                        else currentPlayerC++; //move;
                        break;
                case ARROW_DOWN: //move down;
//                case 'J':
                        nextPos = m_dungeon->get(currentPlayerR + 1, currentPlayerC);
                        if (currentPlayerR >= MAXROWS - 2 || nextPos == '#')//check if valid;
                            return "";
                        else currentPlayerR++; //move;
                        break;
                case ARROW_LEFT: //move left;
//                case 'H':
                        nextPos = m_dungeon->get(currentPlayerR, currentPlayerC - 1);
                        if (currentPlayerC <= 1 || nextPos == '#') //check if valid;
                            return "";
                        else
                            currentPlayerC--; //move;
                        break;
                case '>':
                        if (getdescondMove() == true) //check if at stair;
                        {
                            descend(); //descend to next level;
                            return "";
                        }
                        return "";
                        break;
                case 'g':
                case 'G':
                if(currentPlayerR==m_dungeon->getIdolR()&&currentPlayerC==m_dungeon->getIdolC())//check if at idol.
                {
                    m_player->move(input);
                    m_player->setWin(); //set player status to win;
                    return "";
                    break;
                }
                if(getgetObject() == true)
                {
                    if(m_player->getInventorySize()!= inventoryCap)
                    {
                        pickObject(); //get object;
                    }else
                    {
                        m_dungeon->setBagFull(true); //set inventory to be full;
                        setgetObject(false);
                    }
                    
                }
                return "";
                break;
                case 'i':
                case 'I':
                    clearScreen();
                    m_player->showInventory(); //check bag;
                    getCharacter(); //click any botton to return to the normal page;
                    return "";
                case 'w':
                case 'W':
                    clearScreen();
                    m_player->showInventory(); //check inventory;
                    m_player->wieldWeapon(getCharacter()); //wield weapon;
                    return "w";
                case 'r':
                case 'R':
                    clearScreen();
                    m_player->showInventory(); //check inventory;
                    m_player->readScroll(getCharacter()); //read weapon;
                    return "";
                case 'q':
                case 'Q':
                    return "q";
                    break;
                case 'c':
                case 'C': //cheat;
                    if(m_player->getHit()<=50)
                    m_player->setHit(50);
                    if(m_player->getMaxHit()<=50)
                    m_player->setMaxHit(50);
                    if(m_player->getStrength()<=9)
                    m_player->setStrength(9);
                    return "";
                    break;
                default:
                    return "";
                        break;
                    
            }
            
            
            nextPos = m_dungeon->get(currentPlayerR, currentPlayerC); //check what is under the player;
            
            m_dungeon->setPlayerNext(currentPlayerR, currentPlayerC); //set the potential next pos;
            
            switch (nextPos)
            {
                case ' ':
                {
                    m_player->move(input); //move;
                    return "";
                    break;
                }
                case ')':
                case '?':
                {
                    m_player->move(input);

                        setgetObject(true); //can get object;

                    return "";
                    break;
                    //using find if to get the weapon at that coord
                }
                case '&':
                {
                    m_player->move(input);
                    return "";
                    break;
                }
                case '>':
                {
                    m_player->move(input);
                    setdescondMove(true);
                    return "";
                    break;
                }
                case 'S':
                case 'D':
                case 'G':
                case 'B':
                {
                    //////////////Player turn to fight///////////////
                    m_dungeon->setFight(true);
                    Actors* mon = m_dungeon->getOthers(currentPlayerR, currentPlayerC);
                    m_dungeon->setaMon(mon);
                    m_dungeon->setDeadMon(mon->getRow(), mon->getCol());
                    m_dungeon->setDeadMonNM(mon->getName());
                    m_dungeon->fight(m_player, mon);
                    
                    if (mon != nullptr)
                    {
                        if (m_dungeon->checkDeath(mon)) //check if the monster is dead;
                        {
                            m_dungeon->setDrop(true); //set drop items;
                            m_dungeon->setMonDead(true);
                        }
                        else
                        {
                            m_dungeon->setDrop(false);
                        }
                    }
                    
                    //////////////End player turn////////
                    return "m";
                    break;
                }
            }
        }
    }
}

void Game::setQuit (bool value)
{
    isQuit = value;
}
bool Game::getQuit () const
{
    return isQuit;
}


void Game::play()
{
    string msg = "";
    while(!m_player->getDead() && !m_player->getWin()) //keep doing it until player is dead or winning;
    {
        m_dungeon->display(msg);
        if(msg == "")
        {
            msg = go();
            m_dungeon->monstermove();
        }
        if(msg == "w")
        {
            dontGetChar = true; //dont let the user enter anything for next round;
            msg = go();
        }
        if(msg == "q")
        {
            setQuit(true);
            break;
        }
        if(msg == "m")
        {
            dontGetChar = true; //dont let the user enter anything for next round;
            msg = go();
        }
    }

    if(m_player->getWin()) //if player won the game;
    {
        m_dungeon->display(msg);
        cout<<"You pick up the golden idol"<<endl;
        cout<<"Congratulations, you won!"<< endl;
        cout<<"Press q to exit game."<< endl;
        for (;;)
        {
            char input = getCharacter();
            if (input == 'q' || input == 'Q')
                exit(1);
        }
    }
    
    if(m_player->Actors::getDead()) //if player is dead;
    {
        m_dungeon->display(msg);
        cout<<"Press q to exit game."<< endl;
        for (;;)
        {
            char input = getCharacter();
            if (input == 'q'|| input == 'Q')
                exit(1);
        }
    }
    
    if(getQuit()) //if player enter q and want to quit;
    {
        exit(1);
    }
}

void Game::descend() //player descend to the next level;
{
    int currentLevel = m_dungeon->getLevel();
    int nextLevel = currentLevel + 1;
    player* temp = m_dungeon->getplayer(); //get the previous player;
    m_dungeon = new Dungeon(nextLevel,temp); //generate new level map
    m_player = m_dungeon->getplayer(); //link back to the player;
    descendMove = false;

}

bool Game::pickObject() //pick up the object on the ground;
{
    if(m_player->getInventorySize() == inventoryCap)
    {
        return false;
    }
    else
    {
        int playerR = m_player->getRow();
        int playerC = m_player->getCol();
        for(int i = 0; i < m_dungeon->currentObjSize(); i++)
        {
            int objectR = m_dungeon->getObject(i)->getR();
            int objectC = m_dungeon->getObject(i)->getC();
            if(playerR == objectR && playerC == objectC)
            {
                Objects* temp = m_dungeon->getObject(i);
                m_player->addObject(temp);
                m_dungeon->removeObject(temp);
                m_dungeon->setDisplay(true);
                break;
            }
        }
        
        return true;
        
    }
}



// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

