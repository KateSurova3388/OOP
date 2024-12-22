#include "manager.hpp"

#include <iostream>

Manager::Manager(size_t num,
                 std::initializer_list<std::pair<size_t, bool> > list)
    : count_(num) {
  for (auto& ship_arg : list) {
    if (ship_arg.second) {
      ships_.emplace_back(Ship(ship_arg.first, Ship::Orientation::Horizontal));
    } else {
      ships_.emplace_back(Ship(ship_arg.first, Ship::Orientation::Vertical));
    }
  }
}

const std::vector<Ship>& Manager::get_ships() const { return ships_; }
