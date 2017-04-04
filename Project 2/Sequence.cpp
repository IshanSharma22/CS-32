//
//  Sequence.cpp
//  Project 2
//
//  Created by Ishan Sharma on 1/27/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
        :m_size(0)
{
    //Initalize the the circularly linked dummy node
    head=new Node;
    head->next=head;
    head->previous=head;

}

Sequence::~Sequence(){
    Node * p = head;
    Node * n = head->next;
    
    do                     // Loop through the entire list delteing what p points to next using n to reallign p to the other nodes
    {
        p=n;
        n=p->next;
        delete p;
    }
    while (p!=head);
    
}

bool Sequence::empty() const{
    if (m_size>0)
        return false;
    else
        return true;
}


int Sequence::size() const{
    return m_size;
}


bool Sequence::insert(int pos, const ItemType& value){
    
    if (pos<0 || pos > size())
        return false;
    
    if (pos==size()){                   // If position equals size just insert at the end
        Node * newNode= new Node; // Dynamically create a new Node and give the value passed in
        newNode->m_value=value;
        (head->previous)->next=newNode;
        newNode->previous=(head->previous);
        head->previous=newNode;
        newNode->next=head;
        m_size++;
        return true;
    }
    
    Node *p= head->next;
    
    for (int k=0; k<size(); k++){
        if (k==pos){
            Node * newNode= new Node; // Dynamically create a new Node and give the value passed in
            newNode->m_value=value;
            newNode->previous=p->previous;
            newNode->next=p;
            (p->previous)->next=newNode;
            p->previous=newNode;
            m_size++;
            return true;
        }
        p=p->next;
    }
    
    return true;
}



bool Sequence::get(int pos, ItemType& value) const{
    if (pos >=0 || pos<size()){
    
        Node * p = head->next;
        for (int i=0; i <size(); i++){
            if (i==pos){
                value=p->m_value;
                return true;
            }
            p=p->next;
        }
    }
    return false;
}



int Sequence::insert(const ItemType& value){

    int p=0;
    
    if(empty()){
        Node * newNode= new Node; // Dynamically create a new Node and give the value passed in
        newNode->m_value=value;
        head->next=newNode;    // If the sequence is empty simply add a new element and properly link it to the dummy node
        head->previous=newNode;
        newNode->next=head;
        newNode->previous=head;
        m_size++;
        return p;
    }
    
    p=size();
    Node* k= head->next;
    for (int x=0; x<size(); x++){
        
        if (k->m_value>=value){
            p=x;
            break;
        }
        k=k->next;
    }
    
    insert(p, value);
    return p;
}



Sequence::Sequence(const Sequence& other)
    :m_size(other.m_size)
{
    head= new Node;                 //Intialise the circularlly linked dummy node
    head->next=head;
    head->previous=head;
    
    Node* n;
    
    for (n=other.head->next; n!=other.head; n=n->next){
        Node* nAdd= new Node;          // Dynamically allocate new nodes to the end of the sequence based on other sequence
        nAdd->m_value=n->m_value;
        
        nAdd->next=head;
        nAdd->previous=head->previous;
        
        (head->previous)->next=nAdd;
        head->previous=nAdd;
    }
    
}


Sequence& Sequence::operator=(const Sequence& other){
    if (this != & other){
        Sequence t(other);
        swap(t);
    }
    return *this;
}


bool Sequence::erase(int pos){
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node * p = head->next;
    for (int k=0; k<size(); k++){
        if (pos ==k){
            Node* d=p;
            (p->previous)->next=p->next;
            (p->next)->previous=p->previous;
            delete d;
            m_size--;
            return true;
        }
        p=p->next;
    }
    
    return false;
}

int Sequence::remove(const ItemType& value){
    int nR=0;
    Node * p;
    for (p = head->next; p!=head; p=p->next){
        if (p->m_value==value){
            Node* d=p;
            (p->previous)->next=d->next;       // Saming deleting code as erase
            (p->next)->previous=d->previous;
            p=d->next;
            delete d;
            m_size--;
            nR++;
        }
    }
    return nR;
}

bool Sequence::set(int pos, const ItemType& value){
    if ( pos <0 || pos > size() ){
        return false;
    }
    Node * p = head->next;
    for (int i=0; i <size(); i++){
        if (i==pos){
            p->m_value=value;
            return true;
        }
        p=p->next;
    }
    
    return false;
}

int Sequence::find(const ItemType& value) const{
    
    if (size()>0){
        Node * p = head->next;
        for (int i=0; i <size(); i++){
            if (p->m_value==value)
                return i;
            p=p->next;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    Node*t=other.head;                  // Simply switch the pointers of the dummy node
    other.head=head;
    head=t;
    
    int tsize=other.m_size;
    other.m_size=m_size;
    m_size=tsize;
    
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    int retVal=-1;
    if (seq1.empty() || seq2.empty() || seq2.size()>seq1.size()){
        return -1;
        
    }
    for (int k=0; k<seq1.size(); k++) {
        ItemType s1;
        ItemType s2;
        int t=0;
        seq1.get(k, s1);
        seq2.get(t, s2);
        if (s1==s2){
            int tem=k;
            int x=k;
            
            while (s1==s2) {
                x++;
                t++;
                seq1.get(x, s1);
                seq2.get(t, s2);
                
                if (t==seq2.size())
                    return tem;
            }
        }
    }
    
    return retVal;
    
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence temp(result);  // Create temporary sequnce
   
    while (!temp.empty()){
        temp.erase(0);
    }
    
    if (seq1.empty()){          //Check Conditions
        temp=seq2;
    }
    
    else if (seq2.empty())
        temp=seq1;
    
    ItemType s1;
    ItemType s2;
    
    int x=0;
    int t=0;
    int k=0;
    
    while (x<seq1.size() || t<seq2.size() ){           // Loop through until both sequence reaches the end
        if (x<seq1.size()){
            seq1.get(x, s1);
            temp.insert(k, s1);
            x++;
            k++;
        }
        
        if (t <seq2.size()){
            seq2.get(t, s2);
            temp.insert(k, s2);
            t++;
            k++;
        }
    }
    
    result=temp;
}

