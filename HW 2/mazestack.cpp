//
//  mazestack.cpp
//  HomeWork 2
//
//  Created by Ishan Sharma on 2/4/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//
/*
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack <Coord> st;
    st.push(Coord(sr,sc)); // Push sr,sc on the stack
    maze[sr][sc] = '@'; // Mark with @
    
    while (!st.empty()){
        Coord coordCurr = st.top();
        st.pop();
        if (coordCurr.r()==er && coordCurr.c()==ec)
            return true;
        
        //North
        if ((maze[coordCurr.r()-1][coordCurr.c()] != 'X') && (maze[coordCurr.r()-1][coordCurr.c()] != '@')){
            maze[coordCurr.r()-1][coordCurr.c()] = '@';
            st.push(Coord(coordCurr.r()-1,coordCurr.c()));
        }
        
        //East
        if ((maze[coordCurr.r()][coordCurr.c()+1] != 'X') && (maze[coordCurr.r()][coordCurr.c()+1] != '@')){
            maze[coordCurr.r()][coordCurr.c()+1] = '@';
            st.push(Coord(coordCurr.r(),coordCurr.c()+1));
        }
        
        //South
        if ((maze[coordCurr.r()+1][coordCurr.c()] != 'X') && (maze[coordCurr.r()+1][coordCurr.c()] != '@')){
            maze[coordCurr.r()+1][coordCurr.c()] = '@';
            st.push(Coord(coordCurr.r()+1,coordCurr.c()));
        }
        
        //West
        if ((maze[coordCurr.r()][coordCurr.c()-1] != 'X') && (maze[coordCurr.r()][coordCurr.c()-1] != '@')){
            maze[coordCurr.r()][coordCurr.c()-1] = '@';
            st.push(Coord(coordCurr.r(),coordCurr.c()-1));
        }
    }
    
    return false;
}

*/
