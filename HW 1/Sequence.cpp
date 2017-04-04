//
//  Sequence.cpp
//  Project 2
//
//  Created by Ishan Sharma on 1/18/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence(){
    m_size=0;
}

bool Sequence::empty() const {
    if (m_size>0)
        return false;
    return true;
}

int Sequence::size() const {
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// (e.g., because it's implemented using a fixed-size array) and is
// full.)  Otherwise, leave the sequence unchanged and return false.
// Notice that if pos is equal to size(), the value is inserted at the
// end.
{

    if (pos < 0 || pos > size())
        return false;
    
    if (pos >= DEFAULT_MAX_ITEMS)
        return false;
    
    if (pos==size()){
        m_value[size()]=value;
        m_size++;
        return true;
    }
    
    m_size++;
    
    for (int k=size(); k > pos; k--){
        m_value[k]=m_value[k-1];
    }
    m_value[pos]=value;
    
    return true;
}

int Sequence::insert(const ItemType& value)
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
{
    int p = 0;
    
    for (int k=0; k<size(); k++){
        if (m_value[k]>=value){
            p=k;
            break;
        }
        else
            p=size();
    }
    
    if (p<0 || p>size() || size()>=DEFAULT_MAX_ITEMS)
        return -1;
    
    m_size++;
    
    for (int k=size(); k > p; k--){
        m_value[k]=m_value[k-1];
    }
    m_value[p]=value;
    
    return p;
}

bool Sequence::erase(int pos){
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

    if ( pos >= 0 && pos<size()){
        for (int k = pos; k<size(); k++){
            m_value[k]=m_value[k+1];
        }
        m_size--;
        return true;
    }
    
    return false;
}

int Sequence::remove(const ItemType& value){
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
    int nRemoved=0;
    
    for (int k=0; k<size(); k++){
        if (m_value[k]==value){
            for (int j=k; j<size(); j++){
                m_value[j]=m_value[j+1];
            }
            m_size--;
            nRemoved++;
        }
    }
    return nRemoved;
}

bool Sequence::get(int pos, ItemType& value) const{
    // If 0 <= pos < size(), copy into value the item at position pos
    // in the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    if ( pos >=0 && pos < size()){
        value= m_value[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
    if ( pos >= 0 && pos < size()){
        m_value[pos]=value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
{
    int p=0;
    for (int k=0; k <size(); k++){
        if (m_value[k]==value){
            p=k;
            return p;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    
    ItemType tArray[DEFAULT_MAX_ITEMS];
    
    int tsize=m_size;
    m_size=other.m_size;
    other.m_size=tsize;
    
    for (int k=0; k<DEFAULT_MAX_ITEMS; k++){
        tArray[k]=m_value[k];
        m_value[k]=other.m_value[k];
        other.m_value[k]=tArray[k];
    }
    
}

void Sequence::dump(){
    for (int k=0; k<m_size; k++){
        cerr << m_value[k] << "/";
    }
    cerr << this->insert(10);
}

