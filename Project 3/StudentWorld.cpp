#include "StudentWorld.h"
#include <string>
#include "Compiler.h"

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::getTicks(){
    return m_ticks;
}

int StudentWorld::getWinningNo(){

    
    for (int k=0; k<m_size; k++){
        int count=0;
        for (int i = 0; i<m_size; i++){
            if ((scores[k] > scores[i]) && scores[k]>5)
                count+=1;
        }
        if (count == (m_size-1) && scores[k]>5)
            return k;
        
    }
    
    return (m_currentwinner);
}


void StudentWorld::incScore(int colony){
    scores[colony]+=1;
    
        int count=0;
        for (int i = 0; i<m_size; i++){
            if ((scores[colony] > scores[i]) && scores[colony]>5 )
                count+=1;
        }
        if (count == m_size-1 && scores[colony]>5)
            m_currentwinner=colony;
    
    
}


void StudentWorld::setDisplayText(){
    
    ostringstream oss;
    oss << "Ticks:";        //Update Tick counter display
    oss <<setw(5)<<m_ticks;
    oss<<" -";

    for(int i=0; i<m_size; i++){         //Chnage
        
        if(i==getWinningNo()){
            oss<<"  ";
            oss<<(*(compList[i])).getColonyName() +"*: ";
            oss.fill('0');
            oss << setw(2) << scores[i];
        }
        else{
        oss<<"  ";
        oss<<(*(compList[i])).getColonyName() + ": ";
        oss.fill('0');
        oss << setw(2) << scores[i];
        }
    }
    
    string s = oss.str();
    
    setGameStatText(s);
    
}

int StudentWorld::init(){
    m_ticks=2000;
    
    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    m_size=fileNames.size();
    
    Compiler *compilerForEntrant0, *compilerForEntrant1,
    *compilerForEntrant2, *compilerForEntrant3;
    
    Anthill* ah0,*ah1, *ah2, *ah3;
    
    
    std::string fieldFileName;
    Field f;
    std::string fieldFile = getFieldFilename();
    string s;
    if (f.loadField(fieldFile, s) != Field::LoadResult::load_success){
        setError(fieldFile + " " + s);
        return GWSTATUS_LEVEL_ERROR; // something bad happened!
    }
    
    
    
    for (int i=0; i<VIEW_WIDTH; i++){
        for (int j=0; j<VIEW_WIDTH; j++){
            int x=i;            // initalise variables to incrementors
            int y=j;
            
            Field::FieldItem obj = f.getContentsOf(x,y);        //Get actor
            
            if (obj==Field::FieldItem::anthill0){       // Allocate anthills for each team
                if(m_size>0){
                    compilerForEntrant0= new Compiler;
                    
                    string error;
                    if (! compilerForEntrant0->compile(fileNames[0], error)){
                        setError(fileNames[0]+ " " + error);
                        return GWSTATUS_LEVEL_ERROR;
                    }
                    compList[0]=compilerForEntrant0;
                    
                    ah0 = new Anthill(x, y, 0, this, compilerForEntrant0);
                    data[y][x].push_back(ah0);
                }
            }
    
            if (obj==Field::FieldItem::anthill1){
                if(m_size>1){
                    compilerForEntrant1= new Compiler;
                        
                    string error;
                    if (! compilerForEntrant1->compile(fileNames[1], error)){
                        setError(fileNames[1]+ " " + error);
                        return GWSTATUS_LEVEL_ERROR;
                    }
                    compList[1]=compilerForEntrant1;
                        
                    ah1 = new Anthill(x, y, 1, this, compilerForEntrant1);
                    data[y][x].push_back(ah1);
                    }
            }
            
            if(obj==Field::FieldItem::anthill2){       // Allocate anthills for each team
                
                if (m_size>2){
                    compilerForEntrant2= new Compiler;

                    string error;
                    if (! compilerForEntrant2->compile(fileNames[2], error)){
                        setError(fileNames[2]+ " " + error);
                        return GWSTATUS_LEVEL_ERROR;
                    }
                    compList[2]=compilerForEntrant2;
                    ah2 = new Anthill(x, y, 2, this, compilerForEntrant2);
                    data[y][x].push_back(ah2);
                }

            }
            
            if (obj==Field::FieldItem::anthill3){       // Allocate anthills for each team
                
                if(m_size>3){
                    compilerForEntrant3= new Compiler;
                    
                    string error;
                    if (! compilerForEntrant3->compile(fileNames[3], error)){
                        setError(fileNames[3]+ " " + error);
                        return GWSTATUS_LEVEL_ERROR;
                    }
                    compList[3]=compilerForEntrant3;
                    
                    ah3 = new Anthill(x, y, 3, this, compilerForEntrant3);
                    data[y][x].push_back(ah3);
                }
            
            }
            
            if (obj==Field::FieldItem::rock){       //If rock, new pebble
                Actor * p = new Pebble(x,y,this);
                data[y][x].push_back(p);
            }
            
            
            else if ( obj==Field::FieldItem::grasshopper){
                Actor *p = new babyGrasshopper(x,y,this);       //CHANGE THIS BACK TO BABY
                data[y][x].push_back(p);
            }
            
            else if ( obj ==Field::FieldItem::food){
                Actor * p = new Food(x, y, 6000, this);  ///// ************** CHANGE THIS TO 6000 *********************
                data[y][x].push_back(p);
            }
            
            else if ( obj ==Field::FieldItem::water){
                Actor *p = new PoolOfWater(x, y, this);
                data[y][x].push_back(p);
            }
            
            else if ( obj ==Field::FieldItem::poison){
                Actor *p = new Poison(x, y, this);
                data[y][x].push_back(p);
            }
        }
    
    }
    
    return GWSTATUS_CONTINUE_GAME;
    
}

int StudentWorld::move(){
    
    m_ticks--;
    
    for (int j=0; j<VIEW_WIDTH; j++){
        for (int i=0; i<VIEW_HEIGHT; i++)
        {
            list<Actor*>::iterator it;
            it=data[j][i].begin();
            
            if (data[j][i].size()!=0) {
                
                while (it != data[j][i].end()){ //Iterate through
                    
                    int oldx=((*it)->getX());   //Store old coordinates
                    int oldy=((*it)->getY());
                    
                    if ((*it)->isalive() && !(*it)->getHasMoved())
                        (*it)->doSomething();
                    
                    
                    if (oldx != (*it)->getX() || oldy != (*it)->getY()){   //If any change erase the pointer and readjust
                        Actor* temp = (*it);
                        data[(*it)->getY()][(*it)->getX()].push_back(temp);
                        it=data[j][i].erase(it);
                    }
                    else
                        it++;
                }
            }
        }
    }
    
// Set Has Moved Back to False
    for (int j=0; j<VIEW_WIDTH; j++){
        for (int i=0; i<VIEW_HEIGHT; i++)
        {
            list<Actor*>::iterator it;
            it=data[j][i].begin();
            
            while (it != data[j][i].end()){ //Make sure to se all actors to false
                ((*it)->setHasMoved(false));
                it++;
            }
        }
    }
    
   
// Delete Dead Actors
    for (int j=0; j<VIEW_WIDTH; j++){
        for (int i=0; i<VIEW_HEIGHT; i++)
        {
            list<Actor*>::iterator it;
            it=data[j][i].begin();
            
            while (it != data[j][i].end()){
                if (!(*it)->isalive()){
                    delete (*it);
                    it=data[j][i].erase(it);
                }
                
                else
                    it++;
            }
        }
    }
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
    
    setDisplayText();

    if (m_ticks<=0){
        if(m_currentwinner!=-1){
            setWinner((*compList[m_currentwinner]).getColonyName());
            return GWSTATUS_PLAYER_WON;
        }
        return GWSTATUS_NO_WINNER;      //if ticks
    }
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    for (int j=0; j<VIEW_WIDTH; j++){
        for (int i=0; i<VIEW_HEIGHT; i++)        //Iterate through the grid
        {
            list<Actor*>::iterator it;
            it=data[j][i].begin();
            
            if (data[j][i].size()!=0) {
                
                while (it != data[j][i].end()){     //delete actor then erase pointer
                    delete (*it);
                    it=data[j][i].erase(it);
                }
            }
        }
    }
    
}

StudentWorld::~StudentWorld(){
    cleanUp();
    for (int i=0; i<m_size; i++){
        delete compList[i];
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StudentWorld:: isBlock(int x, int y){
    
    list<Actor*>::iterator it;
    
    
    if (data[y][x].size()==0){  //if list is empty just return false
        return false;
    }
    
    it=data[y][x].begin();  //Else set up iterator
    
    while (it != data[y][x].end()){
        if((*it)->blockInsects())   //if this function returns true, then do so as wll
            return true;
        it++;
    }
    
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void StudentWorld::emitPher(int x, int y, int imgID, int colony){
    list<Actor*>::iterator it;
    
    if (data[y][x].size()==0){
        Actor*p=new Pheromone(imgID,x,y,colony,this);
        data[y][x].push_back(p);
        return;
    }
    
    it=data[y][x].begin();

    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isPher()&& (*it)->getColony()==colony)
            break;
    }

    if ( it == data[y][x].end()){
        Actor*p=new Pheromone(imgID,x,y,colony,this);
        data[y][x].push_back(p);
    }
    
    else{
        int inc= (768 - (*it)->getHP());
        if (inc<256)
            (*it)->incHP(inc);
        else
            (*it)->incHP(256);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////

void StudentWorld::addFood(int x, int y, int amount){
    list<Actor*>::iterator it;
    
    if (data[y][x].size()==0){
        Actor * p = new Food(x, y, amount, this);
        data[y][x].push_back(p);
        return;
    }
    
    it=data[y][x].begin();
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isFoodObj())
            break;
    }
    
    if ( it == data[y][x].end()){
        Actor * p = new Food(x, y, amount, this);
        data[y][x].push_back(p);
    }
    
    else{
        (*it)->incHP(amount);
    }
        
}

bool StudentWorld::isFoodHere(int x, int y){
    
    if (data[y][x].size()==0){
        return false;           // No food here
    }
    
    list<Actor*>::iterator it;
    it=data[y][x].begin();

    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isFoodObj())
            break;
    }
    
    if ( it == data[y][x].end()){
        return false;
    }
    
    else
        return true;
}


int StudentWorld::foodHpHere(int x, int y){
    list<Actor*>::iterator it;
    
    it=data[y][x].begin();
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isFoodObj())
            break;
    }
    
    return (*it)->getHP();
}

void StudentWorld::reduceFoodHere(int x, int y, int amt){
    // Only ever called if foodHpHere function indicates that there is indeed food object at location x,y so no need for checking
    list<Actor*>::iterator it;

    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isFoodObj())
            break;
    }
    
    if (it == data[y][x].end())         // just to be safe :)
        return;
    
    (*it)->decHP(amt);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int StudentWorld::numEnemiesHere(int x, int y, Actor * p, int colony){
    int count1=0;
    if (data[y][x].size()==0){
        return 0;           // No other actors here
    }
    

    if (p->isAnt()){
        list<Actor*>::iterator it1;
        it1=data[y][x].begin();
        
        while (it1!=data[y][x].end()){
            if( (*it1)->isBitableEnemey() && ((*it1)!=p) && ((*it1)->isalive()) && (*it1)->getColony()!=colony)
                count1++;
            it1++;
        }
        return count1;
    }

    int count2=0;
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    while (it!=data[y][x].end()){
        if( (*it)->isBitableEnemey() && ((*it)!=p) && ((*it)->isalive()))
            count2++;
        it++;
    }
    
    return count2;
}

void StudentWorld::attackObjGrass(int x, int y, Actor * p, bool should){
    
    if(should){
        list<Actor*>::iterator it;
        it=data[y][x].begin();
        int i = 0;
    
        int numEnem= numEnemiesHere(x, y, p);
        int target= randInt(1, numEnem);
    
        for (it=data[y][x].begin(); i != target; it++){
            if( (*it)->isBitableEnemey() && ((*it)!=p) && ((*it)->isalive()) )
                i++;
        }
        it--;
        //cerr<<"Actually Attacked"<<endl;
        (*it)->decHP(50);
        
        if((*it)->isAnt()){
            (*it)->setBitten(true);
        }
        
        if ( (*it)->isAdultGrassHopper() && (*it)->isalive()){
            int randN= randInt(1, 2);
            if (randN==1){
                //cerr<<"BiteBack"<<endl;
                attackObjGrass(x, y, (*it), true);
            }
        }
        
        }
}

void StudentWorld::attackObjAnt(int x, int y, Actor*p, int colony){

        list<Actor*>::iterator it;
        it=data[y][x].begin();
        int i = 0;
        
        int numEnem= numEnemiesHere(x, y, p, colony);
        int target= randInt(1, numEnem);
        
        for (it=data[y][x].begin(); i != target; it++){
            if( (*it)->isBitableEnemey() && ((*it)!=p) && ((*it)->isalive()) && (*it)->getColony()!=colony )
                i++;
        }
        it--;
        
        (*it)->decHP(15);
    
        if((*it)->isAnt()){
            (*it)->setBitten(true);
        }
        if ((*it)->isAdultGrassHopper() && (*it)->isalive()){
            int randN= randInt(1, 2);
            if (randN==1){
                //cerr<<"BiteBack"<<endl;
                attackObjGrass(x, y, (*it), true);
            }
        }

}


void StudentWorld::addActor(int x, int y , Actor* p){
    data[y][x].push_back(p);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void StudentWorld::stun(int x, int y){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    while (it!=data[y][x].end()){
        if( (*it)->stunable() && !(*it)->getStunned() && (*it)->isalive()){
            ((*it)->incSleep(2));
            ((*it)->setStunned(true));
        }
        it++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void StudentWorld::poison(int x, int y){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    while (it!=data[y][x].end()){
        if( (*it)->Poisonable() && (*it)->isalive()){
            ((*it)->decHP(150));
        }
        it++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool StudentWorld::isMyAntHillHere(int x, int y, int colony){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    if (data[y][x].size()==0){
        return false;           // No food here
    }
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isAntHill() && (*it)->getColony()==colony)
            break;
    }
    
    if (it == data[y][x].end()){
        return false;
    }
    
    else
        return true;
    
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool StudentWorld::isDanger(int x, int y){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    if (data[y][x].size()==0){
        return false;           // No food here
    }
    
    int count=0;
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isDangerous() && (*it)->isalive()){
            count++;
        }
    }
    
    if (count > 0)
        return true;
    else
        return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool StudentWorld::isPher(int x, int y, int colony){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    if (data[y][x].size()==0){
        return false;
    }
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->isPher() && (*it)->getColony()==colony){
            break;
        }
    }
    
    if ( it == data[y][x].end()){
        return false;
    }
    
    else
        return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool StudentWorld::isOpen(int x, int y){
    list<Actor*>::iterator it;
    it=data[y][x].begin();
    
    if(x>=63||y>=63|| x<=0|| y<=0){
        return false;
    }
    
    if (data[y][x].size()==0){
        return true;
    }
    
    for (it=data[y][x].begin(); it != data[y][x].end(); it++){
        if((*it)->blockInsects()){
            break;
        }
    }
    
    if ( it == data[y][x].end()){
        return false;
    }
    
    else
        return true;
}

