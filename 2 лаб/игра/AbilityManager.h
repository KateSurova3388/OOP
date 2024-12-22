#ifndef ABILITYMANAGER_H  
#define ABILITYMANAGER_H 
#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <memory>

#include "Abilities.h"
#include "GameShip.h"
#include "Exceptions.h"

class Ability;
class DoubleDamage;
class ScanArea;
class Bombardment;
class GameShip;

class AbilityManager{
    friend class GameShip;

    std::queue<int> abilityQueue;

    int generateRandomNumber();
    std::unique_ptr<Ability> getAbility(int idx);

    void addAbilityIdx(int idx);

    public:
    AbilityManager();
    ~AbilityManager();
    void useAbility(GameShip& GameShip);
};

#endif