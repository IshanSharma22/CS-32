//
//  Game.hpp
//  Project 1
//
//  Created by Ishan Sharma on 1/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <string>

using namespace std;

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();

};

#endif /* Game_hpp */
