#pragma once
#include <vector>

#include "ship.hpp"

class Manager {
 public:
  Manager(size_t num, std::initializer_list<std::pair<size_t, bool> > ships);
  const std::vector<Ship>& get_ships() const;

 private:
  size_t count_;
  std::vector<Ship> ships_;
};
