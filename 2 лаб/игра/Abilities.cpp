#include "Abilities.h"

Ability:: ~Ability() = default;

void DoubleDamage::ability(GameShip& GameShip){
    GameShip.setDoubleDamage();
}

void Scanner::ability(GameShip& GameShip){
    GameShip.scanArea();
}

void Bombardment::ability(GameShip& GameShip){
    GameShip.randomBombardment();
    std::cout << "Bombardment applied!" << std::endl;
}