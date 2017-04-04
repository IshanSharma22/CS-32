//
//  ScoreList.cpp
//  Project 2
//
//  Created by Ishan Sharma on 1/20/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//


 
#include "ScoreList.h"

ScoreList::ScoreList()
    :m_sequence()
{
}

bool ScoreList::add(unsigned long score)
{
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

    if (score <=100){
        if (m_sequence.insert(score) != -1){
            return true;
        }
    }
    return false;
}

bool ScoreList::remove(unsigned long score){
    // Remove one instance of the specified score from the score list.
    // Return true if a score was removed; otherwise false.
    if ( m_sequence.find(score)== -1 )
        return false;
    m_sequence.erase(m_sequence.find(score));
    return true;
}

int ScoreList::size() const
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const{
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
    
    if (size()==0){
        return NO_SCORE;
    }
    
    unsigned long minScore=0;
    unsigned long tempScore;
    
    m_sequence.get(0, tempScore);
    
    for (int k =0; k<size(); k++){
        unsigned long tempScore2;
        m_sequence.get(k, tempScore2);
        
        if (tempScore<=tempScore2)
            minScore=tempScore;
        
        else if (tempScore2<tempScore)
            minScore=tempScore2;
    }
    
    return minScore;
}

unsigned long ScoreList::maximum() const {
    if (size()==0){
        return NO_SCORE;
    }

    unsigned long maxScore=0;
    unsigned long tempScore;
    
    m_sequence.get(0, tempScore);
    
    for (int k =0; k<size(); k++){
        unsigned long tempScore2;
        m_sequence.get(k, tempScore2);
        
        if (tempScore>=tempScore2)
            maxScore=tempScore;
        
        else if (tempScore2>tempScore)
            maxScore=tempScore2;
    }
    
    return maxScore;
}

