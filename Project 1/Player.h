//
//  Player.hpp
//  Project 1
//
//  Created by Ishan Sharma on 1/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "globals.h"
#include <string>

using namespace std;


class Arena;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string dropPoisonPellet();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};
#endif
