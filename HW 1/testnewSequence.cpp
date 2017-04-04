//
//  testnewSequence.cpp
//  Project 2
//
//  Created by Ishan Sharma on 1/21/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//


 
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, 10));
    assert(s.insert(0, 20));
    assert(s.size() == 2);
    ItemType x = 999;
    ItemType y=5;
    assert(s.insert(y)==0);
    assert(s.size() == 3);
    
    assert(s.insert(0, 35));
    assert(s.size() == 4);
    
    assert(s.insert(2, 85));
    
    assert(s.size() == 5);
    
    assert(s.get(0, x) && x == 35);
    assert(s.get(1, x) && x == 5);
    assert(s.get(2, x) && x == 85);
    assert(s.get(3, x) && x == 20);
    assert(s.get(4, x) && x == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

