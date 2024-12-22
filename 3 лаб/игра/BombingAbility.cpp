

#include "BombingAbility.h"
#include <iostream>
void BombingAbility::useAbility() {



    for (int i = 0; i < shipManager->getShipCount(); ++i) {
        if(shipManager->getShips()[i]->isDestroyed())
        {
            continue;
        }

        for (int j = 0; j < shipManager->getShips()[i]->getLength(); ++j) {
            if (shipManager->getShips()[i]->getSegmentState(j)!=SegmentState::Destroyed)
            {
                shipManager->getShips()[i]->takeDamage(j,isDoubleDamage);
                isDoubleDamage = false;
                std::cout << "Ship - " << i << " Segment - " << j << std::endl;
                return;
            }
        }


    }



}

BombingAbility::BombingAbility(bool &isDoubleDamage, ShipManager *shipManager):isDoubleDamage(isDoubleDamage),shipManager(shipManager) {
    this->label = "Booming";
}


