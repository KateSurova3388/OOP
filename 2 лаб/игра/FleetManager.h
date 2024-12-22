#ifndef FLEETMANAGER_H  
#define FLEETMANAGER_H 
#include <vector>
#include <stdexcept>

#include "Ship.h"

class FleetManager {
private:
    std::vector<Ship> ships;

public:
    FleetManager(int shipCount, const std::vector<int>& shipSizes);
    ~FleetManager();

    Ship* get_ship(int index);
};
#endif