//
//  main.cpp
//  HomeWork 3
//
//  Created by Ishan Sharma on 2/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//


#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here
class File{

public:
    File (string n);
    virtual ~File();
    string name() const;
    virtual void open() const=0;
    virtual void redisplay() const;
    
private:
    string m_name;
};


////////File implementations////////////

File::File(string n)
    :m_name(n)
{
}

File::~File(){
}

string File:: name() const {
    return m_name;
}

void File::redisplay() const {
    cout << "refresh the screen";
}

/// TextMsg ///////

class TextMsg : public File{
public:
    TextMsg(string n);
    virtual~TextMsg();
    virtual void open() const;
private:
    
};

TextMsg::TextMsg(string n)
:File(n)
{
}

TextMsg::~TextMsg(){
    cout << "Destroying " << File::name() << ", a text message"<<endl;
}

void TextMsg::open() const
{
    cout<< "open text message";
}

///Picture/////

class Picture: public File{
public:
    Picture(string name);
    ~Picture();
    virtual void open() const;
};

Picture::Picture(string n)
    :File(n)
{
}

Picture::~Picture(){
    cout << "Destroying the picture " << File::name()<<endl;
}

void Picture::open() const{
    cout << "show picture";
}

/// Video ////

class Video : public File{
public:
    Video(string n, int l);
    virtual ~Video();
    virtual void open() const;
    virtual void redisplay() const;
    int length() const;
private:
    int m_length;
};

Video::Video(string n, int l)
:File(n)
{
    m_length=l;
}

Video::~Video(){
    cout << "Destroying " << File::name() << ", a video"<<endl;
}

void Video::open() const{
    cout << "play " << length() << " second video";
}

void Video::redisplay() const
{
    cout << "replay video";
}

int Video::length() const{
    return m_length;
}


void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}

