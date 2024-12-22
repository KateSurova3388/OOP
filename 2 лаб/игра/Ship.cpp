#include "Ship.h"

void Ship::set_length(int length) {
    if (length >= 1 && length <= 4) {
        this->length = length;
        conditionArray.resize(length, Condition::Intact);
    }
    else{
    throw std::invalid_argument("Length should be between 1 and 4.");
    }
}

void Ship::set_orientation(Ship::Orientation orientation) {
    this->orientation = orientation;
}

int Ship::get_length() const {
    return this->length;
}

void Ship::damage(int segment){
    if (conditionArray[segment] == Condition::Intact){
        conditionArray[segment] = Condition::Damaged;
    } else if (conditionArray[segment] == Condition::Damaged) {
        conditionArray[segment] = Condition::Destroyed;
    }
}

bool Ship::isDead(){
    for (const auto& segment: conditionArray){
        if (segment != Condition::Destroyed){
            return false;
        }
    }
    return true;
}