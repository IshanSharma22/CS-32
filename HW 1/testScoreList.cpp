//
//  testScoreList.cpp
//  Project 2
//
//  Created by Ishan Sharma on 1/20/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include <iostream>
#include "ScoreList.h"
#include <cassert>

using namespace std;

int main() {
    ScoreList s;
    assert(s.maximum()==NO_SCORE);
    assert(s.minimum()==NO_SCORE);
    
    s.add(0);
    s.add(15);
    s.add(30);
    s.add(40);
    
    assert(s.size()==4);
    assert(s.maximum()==40);
    assert(s.minimum()==0);
    
    assert(!s.add(-100));
    assert(!s.add(-1000));
    
    
    assert(s.remove(15));
    assert(s.size()==3);
    
}


