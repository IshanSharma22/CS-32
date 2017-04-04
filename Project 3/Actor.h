#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"
#include <math.h>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Compiler;

///////////////////////////////////////////////////////////////////////////////////////////////////
class Actor : public GraphObject{
public:
    Actor(int imgID, int startx, int starty, Direction dir, int depth, StudentWorld* s, int HP=1, int colony=-1);
    virtual void doSomething();
    bool isalive();
    virtual void setDead();
    
    //Checker Functions used as an alternative to dynamic cast
    virtual bool blockInsects();
    virtual bool isFoodObj();
    virtual bool isBitableEnemey();
    virtual bool isAdultGrassHopper();
    virtual bool isPher();
    virtual bool isAntHill();
    virtual bool isAnt();
    bool isAntEnemy(int colony);
    
    virtual bool stunable();
    virtual bool Poisonable();
    virtual bool isDangerous();
    
    
    //Functions for easy access in Student World
    void setHasMoved(bool hasit);
    bool getHasMoved();
    
    void setStunned(bool hasit);
    bool getStunned();
    
    void setBitten(bool bitten);
    bool isBitten();
    
    int getSleep();
    void incSleep(int i2);
    void decSleep(int d2=1);
    
    int getColony();
    
    int getHP();
    void incHP(int i1);
    void decHP(int d1=1);
    
    
    //Student World Pointer
    StudentWorld* getSWpointer();
    
private:
    bool m_alive;
    int m_HP;
    bool m_hasMoved;
    int m_sleep;
    bool m_stunned;
    bool m_bitten;
    bool m_block;
    int m_colony;
    StudentWorld* m_SWpointer;
};



////////////////////////////////////////////////////////////////////////////////////////////////////
class Pebble : public Actor {
public:
    Pebble(int sx, int sy, StudentWorld* s);
    virtual bool blockInsects();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class PoolOfWater : public Actor {
public:
    PoolOfWater(int sx, int sy, StudentWorld* s);
    virtual void doSomething();
    virtual bool isDangerous();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class Poison : public Actor {
public:
    Poison(int sx, int sy, StudentWorld* s);
    virtual void doSomething();
    virtual bool isDangerous();
};
///////////////////////////////////////////////////////////////////////////////////////////////////
class Pheromone: public Actor {
public:
    Pheromone(int imgId, int sx, int sy, int colony, StudentWorld*s);
    virtual void doSomething();
    virtual bool isPher();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class Food : public Actor{
public:
    Food(int sx, int sy, int hp, StudentWorld* s);
    virtual bool isFoodObj();
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Anthill: public Actor{
public:
    Anthill(int sx, int sy, int colony, StudentWorld* s, Compiler* program);
    virtual void doSomething();
    virtual bool isAntHill();
private:
    Compiler* m_program;
    int m_imgId;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
class Insect : public Actor{
public:
    Insect(int imgId, int sx, int sy, Direction dir, int depth, int hitP, StudentWorld* s, int colony=-1);
    
    void randomDir();
    bool moveForward();
    
    virtual void setDead();
    virtual bool isBitableEnemey();

};
///////////////////////////////////////////////////////////////////////////////////////////////////

class Ant : public Insect{
public:
    Ant(int imgId, int sx, int sy, int colony, StudentWorld * s, Compiler* program);
    virtual void doSomething();
    virtual bool Poisonable();
    virtual bool stunable();
    virtual bool isAnt();
    void pickFood();
    void lookinFront(int &newx, int &newy);
    
    
private:
    Compiler* m_program;
    int m_foodHeld;
    int m_ic;
    int m_capacity;
    int m_lastRandomNumber;
    bool m_blocked;
};

class GrassHopper : public Insect{
public:
    GrassHopper(int imgId, int sx, int sy, Direction dir, int depth, int hitP, StudentWorld* s);
    
    //void walk();
    bool attemptEatAndSleep();
    
    void setRandomDistance();
    
    void movement();
    
    void DecDistance();
    void setDistance(int newDist);
    int getDistance();
    
private:
    int m_distance;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
class babyGrasshopper : public GrassHopper {
public:
    babyGrasshopper(int sx, int sy, StudentWorld *s);
    virtual void doSomething();
    virtual bool stunable();
    virtual bool Poisonable();
};

///////////////////////////////////////////////////////////////////////////////////////////////////


class AdultGrasshopper : public GrassHopper {
public:
    AdultGrasshopper(int sx, int sy, StudentWorld * s);
    virtual void doSomething();
    virtual bool isAdultGrassHopper();
    bool attack();

};

#endif // ACTOR_H_
