#include "Actor.h"
#include "StudentWorld.h"
#include <math.h>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//Base Class Implementations
Actor::Actor(int imgID, int startx, int starty, Direction dir, int depth, StudentWorld* s, int HP, int colony)
    :GraphObject(imgID, startx, starty, dir, depth)
{
    m_alive=true;
    m_HP=HP;
    m_SWpointer=s;
    m_hasMoved=false;
    m_sleep=0;
    m_stunned=false;
    m_bitten=false;
    m_block=false;
    m_colony=colony;
}

bool Actor::isalive(){
    return m_alive;
}

void Actor::setDead(){
    m_alive=false;
    setVisible(false);
}

int Actor::getHP(){
    return m_HP;
}

void Actor::incHP(int i1){
    m_HP+=i1;
}

void Actor::decHP(int d1){
    m_HP-=d1;
    if (m_HP <=0)
        setDead();
}

bool Actor::blockInsects(){
    return false;
}

StudentWorld* Actor::getSWpointer(){
    return m_SWpointer;
}

void Actor:: setHasMoved(bool hasit){
    m_hasMoved=hasit;
}

bool Actor:: getHasMoved(){
    return m_hasMoved;
}

void Actor::doSomething(){
    return;
}

bool Actor::isFoodObj(){
    return false;
}

bool Actor::isBitableEnemey(){
    return false;
}

bool Actor::isAdultGrassHopper(){
    return false;
}

bool Actor::stunable(){
    return false;
}

int Actor::getSleep(){
    return m_sleep;
}

void Actor::incSleep(int i2)
{
    m_sleep+=i2;
}

void Actor::decSleep(int d2){
    m_sleep=m_sleep-d2;
}

void Actor::setStunned(bool hasit){
    m_stunned=hasit;
}

bool Actor::getStunned(){
    return m_stunned;
}

bool Actor::Poisonable(){
    return false;
}

void Actor::setBitten(bool bitten){
    m_bitten=bitten;
}

bool Actor::isBitten(){
    return m_bitten;
}

bool Actor:: isAnt(){
    return false;
}

int Actor::getColony(){
    return m_colony;
}

bool Actor::isAntEnemy(int colony){
    if ( m_colony != colony)
        return true;
    return false;
}

bool Actor::isAntHill(){
    return false;
}

bool Actor::isDangerous(){
    return false;
}

bool Actor::isPher(){
    return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

//Pebble
Pebble::Pebble(int sx, int sy, StudentWorld* s)
    :Actor(IID_ROCK, sx, sy, right, 1, s)
{
}

bool Pebble:: blockInsects(){
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Pheromone::Pheromone(int imgId, int sx, int sy, int colony, StudentWorld*s):Actor(imgId, sx, sy, right, 2, s, 256, colony){
}

void Pheromone::doSomething(){
    decHP();
    
    if(getHP()<0)
        setDead();
}

bool Pheromone::isPher(){
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

Food::Food(int sx, int sy, int hp, StudentWorld * s)
: Actor(IID_FOOD,sx,sy,right, 2, s, hp)
{
}

bool Food::isFoodObj(){
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

PoolOfWater::PoolOfWater(int sx, int sy, StudentWorld* s) : Actor(IID_WATER_POOL, sx, sy, right, 2, s)
{
}

void PoolOfWater::doSomething(){
    
    getSWpointer()->stun(getX(), getY());
}

bool PoolOfWater::isDangerous(){
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

Poison::Poison(int sx, int sy, StudentWorld * s) : Actor(IID_POISON, sx, sy, right, 2, s)
{
}

void Poison::doSomething(){
    getSWpointer()->poison(getX(), getY());
}

bool Poison::isDangerous(){
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

Anthill::Anthill(int sx, int sy, int colony, StudentWorld* s, Compiler* program):Actor(IID_ANT_HILL, sx, sy, right, 2, s, 8999, colony)
{
    m_program=program;
    
    switch(colony){
        case (0):
            m_imgId=IID_ANT_TYPE0;
            break;
        case (1):
            m_imgId=IID_ANT_TYPE1;
            break;
        case (2):
            m_imgId=IID_ANT_TYPE2;
            break;
        case (3):
            m_imgId=IID_ANT_TYPE3;
            break;
    }
}

void Anthill::doSomething(){
    decHP();
    //std::cerr<<getHP()<<std::endl;
    
    if (getHP()<0){
        setDead();
        return;
    }
    
    if(getSWpointer()->isFoodHere(getX(), getY())){
        //std::cerr<<"FOOD is HERE"<<std::endl;
        int fHere = getSWpointer()->foodHpHere(getX(), getY());
        
        if (fHere < 10000){
            incHP(fHere);
            getSWpointer()->reduceFoodHere(getX(), getY(), fHere);
            //std::cerr<<"Picked UP food"<<std::endl;
        }
        
        else{
            incHP(10000);
            getSWpointer()->reduceFoodHere(getX(), getY(), 10000);
            //std::cerr<<"Picked UP food"<<std::endl;
        }
        
        return;
    }
    
    if (getHP()>=2000){
        Actor* p = new Ant(m_imgId,getX(), getY(), getColony(), getSWpointer(), m_program);
        getSWpointer()->addActor(getX(), getY(), p);
        decHP(1500);
        getSWpointer()->incScore(getColony());
    }

}

bool Anthill::isAntHill(){
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//Insect

Insect::Insect(int imgId, int sx, int sy, Direction dir, int depth, int hitP, StudentWorld * s, int colony): Actor(imgId,sx, sy, dir, 1,s, hitP, colony)
{
    randomDir();
}

void Insect::randomDir(){
    int rdir=randInt(1, 4); //Generate Random direction
    
    switch (rdir){                          //Set Random Direction
        case 1:
            GraphObject::setDirection(up);
            break;
        case 2:
            GraphObject::setDirection(right);
            break;
        case 3:
            GraphObject::setDirection(down);
            break;
        case 4:
            GraphObject::setDirection(left);
            break;
    }
}


void Insect::setDead(){
    getSWpointer()->addFood(getX(), getY(), 100);
    Actor::setDead();
}


bool Insect::isBitableEnemey(){
    return true;
}

bool Insect::moveForward(){
    //Switch Statement in order try and walk in the random direction with random distance
    bool retVal;
    
    switch (getDirection()) {
        case none:
            break;
            
        case up:
            
            if (!getSWpointer()->isBlock(getX(), getY()+1)){    //If there is a pebbble stop and set distan to 0
                moveTo(getX(), getY()+1);
                setStunned(false);
                retVal=true;
            }
            else{
                retVal=false;
            }

            setHasMoved(true);
            return retVal;
            break;
            
        case right:
            if (!getSWpointer()->isBlock(getX()+1, getY())){  //If there is a pebbble stop and set distan to 0
                moveTo(getX()+1, getY());
                setStunned(false);
                retVal=true;
            }
            else{
                retVal=false;
            }
            
            setHasMoved(true);
            return retVal;
            break;
            
        case down:
            if (!getSWpointer()->isBlock(getX(), getY()-1)){   //If there is a pebbble stop and set distan to 0
                moveTo(getX(), getY()-1);
                setStunned(false);
                retVal=true;
            }
            else{
                retVal=false;
            }
            
            setHasMoved(true);
            return retVal;
            break;
            
        case left:
            if (!getSWpointer()->isBlock(getX()-1, getY())){  //If there is a pebbble stop and set distan to 0
                moveTo(getX()-1, getY());
                setStunned(false);
                retVal=true;
            }
            else{
                retVal=false;
            }
            
            setHasMoved(true);  //Set Has Moved to 0
            return retVal;
            break;
            
        default:
            break;
    }
    
    return false;
    //std::cerr<<getDistance()<<std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////


Ant::Ant(int imgId, int sx, int sy, int colony, StudentWorld * s, Compiler* program): Insect(imgId, sx, sy, right, 1, 1500, s, colony)
{
    m_program=program;
    m_foodHeld=0;
    m_ic=0;
    m_capacity=1800;
    m_lastRandomNumber=0;
    m_blocked=false;
}

void Ant::pickFood(){
    int pickup=400;
    if ((m_capacity-m_foodHeld) < 400)
        pickup=m_capacity-m_foodHeld;
    
    if (getSWpointer()->isFoodHere(getX(), getY())){
        //std::cerr<<"Food Involved"<<std::endl;
        int fHere = getSWpointer()->foodHpHere(getX(), getY());
        
        if (fHere < pickup){
            m_foodHeld+=(fHere);
            getSWpointer()->reduceFoodHere(getX(), getY(), fHere);
        }
        
        else{
            m_foodHeld+=pickup;
            getSWpointer()->reduceFoodHere(getX(), getY(), pickup);
        }
        
    }
}

void Ant::lookinFront(int& newx, int& newy){
    
    switch(getDirection()){
        case up:
            newx=getX();
            newy=getY()+1;
            break;
        case down:
            newx=getX();
            newy=getY()-1;
            break;
        case left:
            newy=getY();
            newx=getX()-1;
            break;
        case right:
            newy=getY();
            newx=getX()+1;
            break;
    }
    
    return;
}


void Ant::doSomething(){
    decHP();
    
    
    if (getHP()<=0){
        setDead();
        return;
    }
    
    if (getSleep()>0){
        decSleep();
        return;
    }
    
    Compiler::Command cmd;
    int cc=0;
    
    for (;;){
        if ( ! (*m_program).getCommand(m_ic, cmd)){
            setDead();
            return;
        }
        
        if (cc>=10)
            return;
        
        switch(cmd.opcode){
            case Compiler::moveForward:
            {
                if (moveForward()){
                    setBitten(false);
                    m_blocked=false;
                }
                else{
                    m_blocked=true;
                }
                m_ic++;
                cc++;
                return;
                break;
            }
            
            case Compiler::eatFood:
            {
                if (m_foodHeld>0){
                    if (m_foodHeld<100){
                        incHP(m_foodHeld);
                        m_foodHeld=0;
                    }
                    else{
                        incHP(100);
                        m_foodHeld-=100;
                    }
                        
                }
                m_ic++;
                cc++;
                return;
                break;
            }
            
            case Compiler::dropFood:
            {
                if(m_foodHeld>0){
                    //std::cerr<<"Dropped Food"<<m_foodHeld<<std::endl;
                    getSWpointer()->addFood(getX(), getY(), m_foodHeld);
                    m_foodHeld=0;
                }
                m_ic++;
                cc++;
                return;
                break;
            }
                
            case Compiler::bite:
            {
                int numE=getSWpointer()->numEnemiesHere(getX(), getY(), this, getColony());
                if (numE>0){
                    getSWpointer()->attackObjAnt(getX(), getY(), this, getColony());
                }
                m_ic++;
                cc++;
                return;
                break;
            }
                
            case Compiler::emitPheromone:
            {
                int imgiDtoPass=-1;
                switch(getColony()){
                    case 0:
                        imgiDtoPass=IID_PHEROMONE_TYPE0;
                        break;
                    case 1:
                        imgiDtoPass=IID_PHEROMONE_TYPE1;
                        break;
                    case 2:
                        imgiDtoPass=IID_PHEROMONE_TYPE2;
                        break;
                    case 3:
                        imgiDtoPass=IID_PHEROMONE_TYPE3;
                        break;
                }
                getSWpointer()->emitPher(getX(), getY(), imgiDtoPass, getColony());
                m_ic++;
                cc++;
                return;
                break;
            }
                
            case Compiler::pickupFood:
            {
                pickFood();
                //std::cerr<<"Picked Up Food"<<std::endl;
                m_ic++;
                cc++;
                return;
                break;
            }
            case Compiler::faceRandomDirection:
            {
                randomDir();
                m_ic++;
                cc++;
                return;
                break;
            }
            case Compiler::rotateClockwise:
            {
                Direction newd;
                
                switch(getDirection()){
                    case up:
                        newd=right;
                        break;
                    case right:
                        newd=down;
                        break;
                    case down:
                        newd=left;
                        break;
                    case left:
                        newd=up;
                        break;
                }
                
                setDirection(newd);
                m_ic++;
                cc++;
                return;
                break;
            }
            case Compiler::rotateCounterClockwise:
            {
                Direction newd;
                
                switch(getDirection()){
                    case up:
                        newd=left;
                        break;
                    case right:
                        newd=up;
                        break;
                    case down:
                        newd=right;
                        break;
                    case left:
                        newd=down;
                        break;
                }
                
                setDirection(newd);
                m_ic++;
                cc++;
                break;
            }
            case Compiler::generateRandomNumber:
            {
                int rand=stoi(cmd.operand1);
                m_lastRandomNumber=randInt(0, rand-1);
                m_ic++;
                cc++;
                break;
            }
            case Compiler::goto_command:
            {
                int nic=stoi(cmd.operand1);
                m_ic=nic;
                cc++;
                break;
            }
            case Compiler::if_command:
            {
                switch(stoi(cmd.operand1)){
                    case Compiler::last_random_number_was_zero:
                    {
                        if(m_lastRandomNumber==0)
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_am_carrying_food:
                    {
                        if(m_foodHeld>0)
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_am_hungry:
                    {
                        if(getHP()<=25)
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_am_standing_on_food:
                    {
                        if(getSWpointer()->isFoodHere(getX(), getY()))
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_am_standing_with_an_enemy:
                    {
                        if(getSWpointer()->numEnemiesHere(getX(), getY(), this) > 0)
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_am_standing_on_my_anthill:
                    {
                        if(getSWpointer()->isMyAntHillHere(getX(), getY(), getColony())){
                            m_ic=stoi(cmd.operand2);
                            //std::cerr<<"Standing on Hill"<<std::endl;
                        }
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_was_bit:
                    {
                        if(isBitten())
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_was_blocked_from_moving:
                    {
                        if(m_blocked)
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                    case Compiler::i_smell_pheromone_in_front_of_me:
                    {
                        int nx,ny;
                        lookinFront(nx, ny);
                        if(getSWpointer()->isPher(getX(), getY(), getColony()))
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                        
                    case Compiler::i_smell_danger_in_front_of_me:
                    {
                        int nx,ny;
                        lookinFront(nx, ny);
                        if((getSWpointer()->numEnemiesHere(nx, ny, this, getColony()) > 0) || (getSWpointer()->isDanger(nx, ny)) )
                            m_ic=stoi(cmd.operand2);
                        else
                            m_ic++;
                        break;
                    }
                }
                cc++;
            }
        }
    
    }

}



bool Ant::isAnt(){
    return true;
}

bool Ant::stunable(){
    return true;
}

bool Ant::Poisonable(){
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

GrassHopper::GrassHopper(int imgId, int sx, int sy, Direction dir, int depth, int hitP, StudentWorld* s)
:Insect(imgId, sx, sy, dir, 1, hitP, s)
{
    setRandomDistance();
}

void GrassHopper::setRandomDistance(){
    int rdis = randInt(2, 10);
    m_distance=rdis;
}

void GrassHopper::setDistance(int newDist){
    m_distance=newDist;
}

int GrassHopper::getDistance(){
    return m_distance;
}

void GrassHopper::DecDistance(){
    m_distance--;
}

bool GrassHopper::attemptEatAndSleep(){
    
    if (getSWpointer()->isFoodHere(getX(), getY())){
        //std::cerr<<"Food Involved"<<std::endl;
        int fHere = getSWpointer()->foodHpHere(getX(), getY());
        
        if (fHere < 200){
            incHP(fHere);
            getSWpointer()->reduceFoodHere(getX(), getY(), fHere);
        }
        
        else{
            incHP(200);
            getSWpointer()->reduceFoodHere(getX(), getY(), 200);
        }
        
        int randomN= randInt(1, 2);
        //std::cerr<<getHP()<<std::endl;
        
        if (randomN==1){
            incSleep(2);
            return true;
        }
        
    }
    return false;
}

void GrassHopper::movement(){
    if (getDistance()==0){      // If the distance is 0, get new random direction & new distance annnnd then walk
        randomDir();
        setRandomDistance();
        
        if(moveForward()){
            DecDistance();
        }
        else
            setDistance(0);
        
        incSleep(2);
        setHasMoved(true);
    }
    
    else{
        if(moveForward()){
            DecDistance();
        }
        else
            setDistance(0);
        
        incSleep(2);
        setHasMoved(true);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////

// BabyGrass

//GrassHopper(int imgId, int sx, int sy, Direction dir, int depth, int hitP, StudentWorld* s)
babyGrasshopper::babyGrasshopper(int sx, int sy, StudentWorld* s) : GrassHopper(IID_BABY_GRASSHOPPER, sx, sy, right, 1, 500, s)
{
}

void babyGrasshopper::doSomething(){
    //std::cerr<<getHP()<<std::endl;
    decHP();
    
    if (getHP()<=0){
        setDead();
        return;
    }
    
    if(getSleep() > 0){             //If sleep is still greater than 0 decrement it and return
        decSleep();
        //std::cerr<<"Sleept"<<std::endl;
        return;
    }
    
    if (getHP()>=1600){
        Actor* p = new AdultGrasshopper(getX(), getY(), getSWpointer());
        getSWpointer()->addActor(getX(), getY(), p);
        setDead();
        return;
    }
    
    
    if(attemptEatAndSleep()){
        //std::cerr<<"Sleep Increased"<<std::endl;
        return;
    }
    
    movement();
}

bool babyGrasshopper::stunable(){
    return true;
}

bool babyGrasshopper::Poisonable(){
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Adult Grasshopper
AdultGrasshopper::AdultGrasshopper(int sx, int sy, StudentWorld * s): GrassHopper(IID_ADULT_GRASSHOPPER,sx,sy,right,1,1600,s)
{
}

bool AdultGrasshopper::attack(){
    
    int randN1= randInt(1, 3);
    int numEnem=getSWpointer()->numEnemiesHere(getX(), getY(), this);
    
    if (randN1==1 && numEnem > 0){
        getSWpointer()->attackObjGrass(getX(), getY(), this, true);
        incSleep(2);
        return true;
    }
    
    return false;
}

void AdultGrasshopper::doSomething(){
    decHP();
    
    if (getHP()<=0){
        setDead();
        return;
    }
    
    if(getSleep() > 0){             //If sleep is still greater than 0 decrement it and return
        decSleep();
        //std::cerr<<"Sleept"<<std::endl;
        return;
    }
    
    if (attack()){
        return;
    }
    
    int randNo= randInt(1, 10);     //Generate Random number in order to dictate random jumping
    if(randNo==1){
        int ranAngle=randInt(0, 359);
        int ranRad=(ranAngle*3.14)/180;
    
        int ranDistance=randInt(1, 10);
    
        int nx=getX()+ ((ranDistance)*cos(ranRad));
        int ny=getY()+((ranDistance)* sin(ranRad));
    
        if(getSWpointer()->isOpen(nx, ny)){
            moveTo(nx, ny);
            incSleep(2);
            return;
        }
    
    }

    
    if(attemptEatAndSleep()){
        //std::cerr<<"Sleep Increased"<<std::endl;
        return;
    }
    
    movement();
    
    
}

bool AdultGrasshopper::isAdultGrassHopper(){
    return true;
}

