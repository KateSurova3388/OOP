
#ifndef OOP_ABILITYMANAGER_H
#define OOP_ABILITYMANAGER_H
#include<iostream>
#include <vector>
#include <queue>
#include <memory>
#include <random>
#include <algorithm>
#include "IAbility.h"
#include "DoubleDamageAbility.h"
#include "ScannerAbility.h"
#include "BombingAbility.h"

class AbilityManager {
    std::vector<std::shared_ptr<IAbility>> abilityQueue;
    GameBoard* gameBoard;
    bool &isDoubleDamage;
    ShipManager* shipManager;
public:
    std::string getAbilityStr();
    int getLen();
    AbilityManager(bool &isDoubleDamage,GameBoard* gameBoard,ShipManager* shipManager);
    ~AbilityManager();
    void addRandomAbility();
    void useNextAbility();
    std::string getTopLabel();
    void setNewFields(GameBoard* gameBoard,ShipManager* shipManager);
    void loadAbility(std::vector<std::string> newAbility);
};


#endif //OOP_ABILITYMANAGER_H
