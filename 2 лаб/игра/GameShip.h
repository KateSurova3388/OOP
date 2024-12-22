#ifndef GAMEFIELD_H  
#define GAMEFIELD_H 
#include <iostream>
#include <vector>
#include <stdexcept>

#include <deque>
#include <random>

#include "Ship.h"
#include "FleetManager.h"
#include "Abilities.h"
#include "AbilityManager.h"
#include "Exceptions.h"

class DoubleDamage;
class Scanner;
class Bombardment;
class AbilityManager;

class GameShip{
    private:
        int width;
        int height;
        AbilityManager& abilityManager;
        enum class CellStatus { Unknown, Empty, Occupied, Damaged, Destroyed };
        std::vector <std::vector<CellStatus>> Field;
        std::vector<std::vector<std::pair<Ship*, int>>> ShipCoordinates;
  
        std::vector<std::pair<int, int>> occupiedCells;
        bool doubleDamage;

        friend class DoubleDamage;
        friend class Scanner;
        friend class Bombardment;
        friend class AbilityManager;

        void randomBombardment();
        void scanArea();
        void setDoubleDamage(bool status = true);
        
        void generateAbilityIdx(AbilityManager& abilityManager);
        bool CheckShipCondition(Ship* ship);

    public: 
        GameShip(int width, int height, AbilityManager& abilityManager);
        ~GameShip();
        GameShip& operator=(GameShip&& other) noexcept;
        GameShip(GameShip&& other) noexcept;
        GameShip& operator=(const GameShip& other);
        void setShip(Ship* ship, const std::pair<int, int>& coordinates, Ship::Orientation orientation);
        void attackCell(int y, int x);
        bool canPlaceShip(Ship* ship, int x, int y, int dx, int dy);
        void plotField();
        void getOnlyOccupiedCells();
        
};
#endif