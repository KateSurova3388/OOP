#ifndef OOP_SHIP_H
#define OOP_SHIP_H
#include<iostream>
#include<vector>
#include "SegmentState.h"
#include "LocationShipError.h"
class Ship{

private:
    int length;
    bool isHorizontal;
    std::vector<SegmentState> segments;
    int x,y;

public:

    Ship(int length);

    int getLength();
    bool getIsHorizontal();
    bool isDestroyed();
    void setPosition(int x,int y,bool isHorizontal);
    std::pair<int,int> getPosition();
    void destroySegment(int segmentIndex);
    void rotateShip();
    void setSegmentsStates(std::vector<SegmentState> newSegments);
    SegmentState getSegmentState(int segmentIndex);
    std::string getShipInfoStr();
    bool takeDamage(int segmentIndex, bool isDoubleDamage);

};


#endif
