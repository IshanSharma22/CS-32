//
//  Rat.hpp
//  Project 1
//
//  Created by Ishan Sharma on 1/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef Rat_h
#define Rat_h


class Arena;

class Rat
{
public:
    // Constructor
    Rat(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif
