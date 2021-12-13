//
//  Objects.hpp
//  CS32 Project 3
//
//  Created by Siyuan Li on 5/15/20.
//  Copyright © 2020 Siyuan Li. All rights reserved.
//
#ifndef Objects_h
#define Objects_h

#include<iostream>
#include<string> // for string class
#include"utilities.h"
#include"globals.h"
using namespace std;

class Objects
{
public:
    Objects(string name);
    string getName() const;
    void setName(string n);
    void setDamage(int d);
    void setBonus(int b);
    int getDamage() const;
    int getBonus() const;
    int getR() const; int getC() const;
    void setR(int row); void setC(int col);
    bool isCreated() const; void setCreated();
private:
    string name;
    int damage;
    int bonus;
    int r; int c;
    bool created;
};

class weapon : public Objects
{
public:
    weapon(string name);
    void use();
private:
    string action;
    int bonus;
    int damage;

};

class scroll :public Objects
{
public:
    scroll(string name);
    
private:
    void use();
};
#endif
