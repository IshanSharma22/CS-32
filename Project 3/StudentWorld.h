#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h" 
#include "Actor.h"
#include <list>
#include <string>
#include <sstream>
#include <iomanip>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;

class StudentWorld : public GameWorld
{
public:
	
    StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        m_ticks=2000;
        m_currentwinner=-1;

	}

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    ~StudentWorld();
  
    void addActor(int x, int y , Actor* p);

    //Pebble helper functions
    bool isBlock(int x, int y);
    
    //Food Helper Functions
    void addFood( int x, int y, int amount);
    bool isFoodHere(int x, int y);
    int foodHpHere(int x, int y);
    void reduceFoodHere(int x, int y, int amt);
    
    //Adult GrassHopper Helper Functions
    int numEnemiesHere(int x, int y, Actor * p, int colony=-1);
    void attackObjGrass(int x, int y, Actor * p, bool should);
    bool isOpen(int x, int y);
    
    // Pool of Water Helpers
    void stun(int x, int y);
    
    //Poison Help
    void poison(int x, int y);
    
    //Ant help
    bool isMyAntHillHere(int x, int y, int colony);
    bool isDanger(int x, int y);
    void emitPher(int x, int y, int imgID, int colony);
    bool isPher(int x, int y, int colony);
    void attackObjAnt(int x, int y, Actor*p, int colony);
    //Score
    void incScore(int colony);
    int getWinningNo();

    void setDisplayText();
    int getTicks();

private:
    int m_ticks;
    std::list<Actor*> data[VIEW_HEIGHT][VIEW_WIDTH];
    int scores[4];
    Compiler* compList[4];
    int m_currentwinner;
    int m_size;
};


#endif // STUDENTWORLD_H_
