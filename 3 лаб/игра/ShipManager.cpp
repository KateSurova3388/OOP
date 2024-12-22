#include "ShipManager.h"

ShipManager::ShipManager(std::vector<int> shipsData) {
    this->shipCount = shipsData.size();
    for (int i = 0; i < shipCount; ++i) {
        Ship* ship = new Ship(shipsData[i]);
        this->ships.push_back(ship);
    }
}



bool ShipManager::hitShip(int x, int y, int index,bool isDoubleDamage)
{
    if(ships[index]->isDestroyed())
    {
        return false;
    }

    if(this->ships[index]->getIsHorizontal())
    {
        return this->ships[index]->takeDamage(x - this->ships[index]->getPosition().first,isDoubleDamage);
    } else
    {
        return this->ships[index]->takeDamage(y - this->ships[index]->getPosition().second,isDoubleDamage);
    }
}

int ShipManager::getShipCount() const {
    return this->shipCount;
}

std::vector<Ship*>& ShipManager::getShips() {
    return ships;
}

ShipManager::~ShipManager() {
    for (int i = 0; i < this->shipCount; ++i) {
        delete ships[i];
    }
}

bool ShipManager::isAllShipDestroyed() {
    for (int i = 0; i < this->shipCount; ++i) {
        if(!this->ships[i]->isDestroyed())
        {
            return false;
        }
    }
    return true;
}

SegmentState ShipManager::getSegmentState(int x, int y, int index) {
    if(this->ships[index]->getIsHorizontal())
    {
        return this->ships[index]->getSegmentState(x - this->ships[index]->getPosition().first);
    } else
    {
        return this->ships[index]->getSegmentState(y - this->ships[index]->getPosition().second);
    }
}

std::string ShipManager::getShipInfoStr(int index) {
    return this->ships[index]->getShipInfoStr() + "\n";
}

ShipManager::ShipManager(const ShipManager& other) : shipCount(other.shipCount) {
    for (Ship* ship : other.ships) {
        ships.push_back(new Ship(*ship));
    }
}


ShipManager::ShipManager(ShipManager&& other) noexcept
        : ships(std::move(other.ships)), shipCount(other.shipCount) {
    other.shipCount = 0;
}


ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {

        for (Ship* ship : ships) {
            delete ship;
        }
        ships.clear();


        for (Ship* ship : other.ships) {
            ships.push_back(new Ship(*ship));
        }

        shipCount = other.shipCount;
    }
    return *this;
}

ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
    if (this != &other) {
        for (Ship* ship : ships) {
            delete ship;
        }
        ships.clear();

        ships = std::move(other.ships);
        shipCount = other.shipCount;
        other.shipCount = 0;
    }
    return *this;
}

void ShipManager::resetShips(std::vector<Ship*> ships) {
    for (int i = 0; i < this->shipCount; ++i) {
        delete this->ships[i];
    }
    this->ships.clear();
    for (int i = 0; i < this->shipCount; ++i) {
        this->ships.push_back(ships[i]);
    }


}

