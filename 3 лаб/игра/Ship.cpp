#include "Ship.h"

Ship::Ship(int length) {
    if (length > 4)
    {
        length = 4;
    }

    if (length < 1)
    {
        length = 1;
    }

    this->length = length;
    this->segments.resize(length, SegmentState::Intact);
}

int Ship::getLength() {
    return this->length;
}

bool Ship::getIsHorizontal() {
    return isHorizontal;
}

bool Ship::isDestroyed() {
    for (const auto& state : segments) {
        if (state != SegmentState::Destroyed) {
            return false;
        }
    }
    return true;
}

bool Ship::takeDamage(int segmentIndex,bool isDoubleDamage) {
    if (this->segments.size() <= segmentIndex || segmentIndex < 0)
    {
        throw LocationShipError("Wrong point of ship location");
    }
    if (isDoubleDamage)
    {
        segments[segmentIndex] = SegmentState::Destroyed;
    }
    else
    {
        if (segments[segmentIndex] == SegmentState::Intact) {
            segments[segmentIndex] = SegmentState::Damaged;
        }else if (segments[segmentIndex] == SegmentState::Damaged) {
            segments[segmentIndex] = SegmentState::Destroyed;
        }
    }
    if(this->isDestroyed())
    {
        return true;
    }
    return false;

}





std::string Ship::getShipInfoStr(){

    std::string segmentsStr =std::to_string(length)+" "+ std::to_string(x) + " " + std::to_string(y)+" "+ std::to_string(isHorizontal)+" ";
    for (int i = 0; i < this->length; ++i) {
        if (this->segments[i] == SegmentState::Intact)
            segmentsStr += "0";
        if (this->segments[i] == SegmentState::Damaged)
            segmentsStr += "1";
        if (this->segments[i] == SegmentState::Destroyed)
            segmentsStr += "2";
    }
    return segmentsStr;
}

void Ship::rotateShip() {
    this->isHorizontal = !(this->isHorizontal);
}

SegmentState Ship::getSegmentState(int segmentIndex) {
    return segments[segmentIndex];
}

void Ship::setPosition(int x, int y,bool isHorizontal) {
    this->x = x;
    this->y = y;
    this->isHorizontal = isHorizontal;
}

std::pair<int,int> Ship::getPosition() {
    return std::pair<int,int>{x,y};
}

void Ship::destroySegment(int segmentIndex) {
    segments[segmentIndex] = SegmentState::Destroyed;
}

void Ship::setSegmentsStates(std::vector<SegmentState> newSegments) {
    for (int i = 0; i < this->length; ++i) {
        this->segments[i] = newSegments[i];
    }
}
