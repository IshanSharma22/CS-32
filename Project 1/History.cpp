//
//  History.cpp
//  Project 1
//
//  Created by Ishan Sharma on 1/13/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//
#include "History.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>
using namespace std;

History::History(int nRows, int nCols)
    : m_nRows(nRows), m_nCols(nCols)
{
    
    for (int a=1; a<=m_nRows; a++){
        for (int b=1; b<=m_nCols; b++){
            m_history_grid[a-1][b-1]=0;
        }
    }
}

bool History::record(int nRows, int nCols){
    if(nRows>m_nRows || nCols>m_nCols || nRows<1 || nCols<1 ){
        return false;
    }
    
    else
    m_history_grid[nRows-1][nCols-1]+=1;
    
    
    
    return true;
}

void History::display() const{
    char historyDisplay[MAXROWS][MAXCOLS];
    
    for (int a=0; a<m_nRows; a++){
        for (int b=0; b<m_nCols; b++){
            
            if (m_history_grid[a][b]==0)
                historyDisplay[a][b] = '.';
            else if (m_history_grid[a][b]<=26)
                historyDisplay[a][b] = 'A' + m_history_grid[a][b] - 1;
            else
                historyDisplay[a][b]='Z';
        }
    }
    
    for (int a=0; a < m_nRows; a++){
        for (int b=0; b< m_nCols; b++){
            cout << historyDisplay[a][b];
        }
        cout << endl;
    }
    cout << endl;
}

