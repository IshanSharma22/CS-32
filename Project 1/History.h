//
//  History.hpp
//  Project 1
//
//  Created by Ishan Sharma on 1/13/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_nRows;
    int m_nCols;
    int m_history_grid[MAXROWS][MAXCOLS];
    
};

#endif /* History_h */
