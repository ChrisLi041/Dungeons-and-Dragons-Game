#include "Objects.h"

Objects::Objects(string name)
:name(name)
{};

bool Objects::isCreated() const
{
    return created;
}

void Objects::setCreated()
{
    created = true;
}

string Objects::getName() const
{
    return name;
}

void Objects::setDamage(int d)
{
    damage = d;
}

void Objects::setBonus(int b)
{
    bonus = b;
}

void Objects::setName(string n)
{
    name = n;
}

int Objects::getDamage() const
{
    return damage;
}
int Objects::getBonus() const
{
    return bonus;
}

int Objects::getR() const
{
    return r;
}
int Objects::getC() const
{
    return c;
}
void Objects::setR(int row)
{
    r = row;
}
void Objects::setC(int col)
{
    c = col;
}

weapon::weapon(string name)
:Objects(name)
{
    if(name == "mace")
    {
        setBonus(0);
        setDamage(2);
    }
    else if(name == "short sword")
    {
        setBonus(0);
        setDamage(2);
    }
    else if(name == "long sword")
    {
        setBonus(2);
        setDamage(4);
    }
    else if(name == "magic axes")
    {
        setBonus(5);
        setDamage(5);
    }
    else if(name == "magic fangs")
    {
        setBonus(3);
        setDamage(2);
    }
};

scroll::scroll(string name)
    : Objects(name)
{
    setDamage(2);
    setBonus(3);
}

void weapon::use()
{
    cout<<"hit";
}

void scroll::use()
{
    cout<<"read";
}

