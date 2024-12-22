#include "FleetManager.h"

FleetManager::FleetManager(int shipCount, const std::vector<int>& shipSizes) {
    if (shipCount != shipSizes.size()) {
        throw std::invalid_argument("Ship count must match the number of sizes.");
    }
    for (int size = 0; size < shipCount; size++) {
        if (shipSizes[size] < 1 || shipSizes[size] > 4) {
            throw std::invalid_argument("Ship size must be between 1 and 4.");
        }
        Ship new_ship;
        new_ship.set_length(shipSizes[size]);
        ships.emplace_back(new_ship); 
    }
}

FleetManager::~FleetManager() {
}

Ship* FleetManager::get_ship(int index){
    if (index<0 || index >= ships.size()){
        throw std::invalid_argument("Invalid index");
    }
    return &ships[index];
}