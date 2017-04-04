//
//  Sequence.hpp
//  Project 2
//
//  Created by Ishan Sharma on 1/27/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include <string>

typedef std::string ItemType;

class Sequence
{
public:
    Sequence(); //Done
    Sequence(const Sequence& other); // Copy Constructor //Done
    Sequence& operator=(const Sequence& other); // Asignment Operator //Done
    ~Sequence(); //Destructor //Done
    bool empty() const; //Done
    int size() const; //Done
    bool insert(int pos, const ItemType& value); //Done
    int insert(const ItemType& value); //Done
    bool erase(int pos);//Done
    int remove(const ItemType& value); //Done
    bool get(int pos, ItemType& value) const; //Done
    bool set(int pos, const ItemType& value); //Done
    int find(const ItemType& value) const; //Done
    void swap(Sequence& other); // Done
    
private:
    struct Node{
        ItemType m_value;
        Node * next;
        Node * previous;
    };
    int m_size;
    Node * head;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif /* Sequence_hpp */
