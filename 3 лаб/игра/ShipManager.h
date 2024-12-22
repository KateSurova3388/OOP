#ifndef OOP_SHIPMANAGER_H
#define OOP_SHIPMANAGER_H
#include <vector>
#include "Ship.h"
#include "SegmentState.h"
class ShipManager{
private:
    std::vector<Ship*> ships;
    int shipCount;

public:
    ShipManager(std::vector<int> sizes);
    ~ShipManager();
    bool hitShip(int x,int y, int index,bool isDoubleDamage);
    bool isAllShipDestroyed();
    int getShipCount() const;
    std::vector<Ship*>& getShips();
    SegmentState getSegmentState(int x,int y, int index);
    std::string getShipInfoStr(int index);
    void resetShips(std::vector<Ship*> ships);
    ShipManager& operator=(ShipManager&& other) noexcept;
    ShipManager& operator=(const ShipManager& other);
    ShipManager(ShipManager&& other) noexcept;
    ShipManager(const ShipManager& other);
};

#endif
