//
//  Navigator.cpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/11/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "provided.h"
#include "MyMap.h"
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "suport.h"
using namespace std;


string direction(double angle);

string direction(double angle){
    if (angle>= 0 && angle<=22.5){
        return "east";
    }
    else if ( angle > 22.5 && angle <=67.5){
        return "northeast";
    }
    else if ( angle > 67.5 && angle <=112.5){
        return "north";
    }
    else if ( angle > 112.5 && angle <=157.5){
        return "northwest";
    }
    else if ( angle > 157.5 && angle <=202.5){
        return "west";
    }
    else if ( angle > 202.5 && angle <=247.5){
        return "southwest";
    }
    else if ( angle > 247.5 && angle <=292.5){
        return "south";
    }
    else if ( angle > 292.5 && angle <=337.5){
        return "southeast";
    }
    else if ( angle > 337.5 && angle <=360){
        return "east";
    }
    else
        return "north";
}

    void navMapper(MyMap<PrioGeoCord, PrioGeoCord> &cf, vector<NavSegment> & dir, PrioGeoCord end, PrioGeoCord start){
    PrioGeoCord* prevPoint;
    PrioGeoCord current=end;
    
    const GeoCoord p;
    const GeoCoord c;
    
    prevPoint=cf.find(current);
    
    while((*prevPoint).name!="SONIPATHYRANAISHANSHARMA"){       // Loop until we reache the temrinating condition specified in navigate
        
        GeoSegment geos1;                                          // Create GeoSegment by using MyMap cf for proceed style navigation
        geos1.start=(*prevPoint).geo;
        geos1.end=current.geo;
        double a2=angleOfLine(geos1);
        string as2= direction(a2);
        double d= distanceEarthMiles((*prevPoint).geo, current.geo);
        
        NavSegment navp(as2, current.name, d, geos1);            // Add onto to vector
        dir.push_back(navp);
        
        if((*prevPoint).name != current.name){
            GeoSegment gs1, gs2;                                //Get two Geosegments in order to dtermine angle of turn
            gs2.start=(*prevPoint).geo;
            gs2.end= current.geo;
            PrioGeoCord*pp=cf.find(*prevPoint);
            gs1.start=(*pp).geo;
            gs1.end=(*prevPoint).geo;
            double ang1=angleBetween2Lines(gs1, gs2);
            string angs1;
            if(ang1<180)
                angs1="left";
            else if (ang1>=180)
                angs1="right";
            NavSegment navt (angs1, current.name);
            dir.push_back(navt);                                // Add turn nav segment to vector
        }
    
        current=(*prevPoint);
        prevPoint=cf.find(*prevPoint);
    }
    
    reverse(dir.begin(), dir.end());                            //Reverse vector
}

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;

private:
    AttractionMapper m_am;
    SegmentMapper m_sm;
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    MapLoader ml;
    if(!ml.load(mapFile)){
        return false;
    }
    
    m_am.init(ml);
    m_sm.init(ml);
    
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    MyMap<PrioGeoCord, PrioGeoCord> cameFrom;               // Initialise two MyMaps and one priority queue
    MyMap<PrioGeoCord, double> distanceSoFar;
    
    priority_queue<PrioGeoCord> geoPrioQ;
    
    if(directions.size()>0){
        directions.clear(); //DOES THIS WORK
    }
    
    GeoCoord startAttrac;
    GeoCoord endAttrac;
    
    if ( !m_am.getGeoCoord(start, startAttrac)){                //if start or end is not found return appropriate error
        return NAV_BAD_SOURCE;
    }
    
    if ( !m_am.getGeoCoord(end, endAttrac)){
        return NAV_BAD_DESTINATION;
    }

    PrioGeoCord ed;
    ed.geo=endAttrac;
    ed.priority=0;
    
    PrioGeoCord st;
    st.geo=startAttrac;
    st.priority=0;
    
    PrioGeoCord null;                       // This node is there to have a stopping condition
    null.name="SONIPATHYRANAISHANSHARMA";  // Random string that indicates reaching the end
    
    vector<StreetSegment> streets;
    streets = m_sm.getSegments(startAttrac);
    
    st.name=streets[0].streetName;
    
    geoPrioQ.push(st);                      //Push first Node onto list
    
    cameFrom.associate(st, null);
    distanceSoFar.associate(st, 0);
    
    while(!geoPrioQ.empty()){               //Loop until priority queue is not empty
        PrioGeoCord curr = geoPrioQ.top();
        geoPrioQ.pop();
        
        streets = m_sm.getSegments(curr.geo);
        
        for (int i=0; i<streets.size(); i++){
            for(int j=0; j<streets[i].attractions.size(); j++){             //If curr geocoord is on a segment that contains end stop
                if(streets[i].attractions[j].geocoordinates==endAttrac){
                    ed.name=streets[i].streetName;
                    curr.name=streets[i].streetName;
                    cameFrom.associate(ed, curr);
                    navMapper(cameFrom, directions, ed, st);
                    return NAV_SUCCESS;
                }
            }
        }

        for( int i=0; i<streets.size(); i++){               //For every street segment generate two options
            PrioGeoCord op1;
            PrioGeoCord op2;
            
            op1.geo=streets[i].segment.start;
            op2.geo=streets[i].segment.end;
            
            op1.name=streets[i].streetName;
            op2.name=streets[i].streetName;
            
            double newdist= *(distanceSoFar.find(curr)) + distanceEarthMiles(curr.geo, op1.geo);       //Calculate distance travelled if continue to this point
            double*p=distanceSoFar.find(op1);
            if (!p || newdist < (*p)){
                distanceSoFar.associate(op1, newdist);              // associate new distance
                double prio = newdist + distanceEarthMiles(endAttrac, op1.geo);
                op1.priority=prio;                                  //calculate priotiy
                geoPrioQ.push(op1);                         // push onto queue
                cameFrom.associate(op1, curr);          // update map that tracks the path taken
            }
            
            double newdist2= *(distanceSoFar.find(curr)) + distanceEarthMiles(curr.geo, op2.geo);
            double*p2=distanceSoFar.find(op2);
            if (!p2 || newdist2 < (*p2)){
                distanceSoFar.associate(op2, newdist2);             // associate new distance
                double prio2 = newdist2 + distanceEarthMiles(endAttrac, op2.geo);   //calculate priotiy
                op2.priority=prio2;
                geoPrioQ.push(op2);                     // push onto queue
                cameFrom.associate(op2, curr);          // update map that tracks the path taken
            }
            
        }
    }
    
    return NAV_NO_ROUTE;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
