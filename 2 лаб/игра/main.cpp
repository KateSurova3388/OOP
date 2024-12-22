#include <iostream>
#include "Ship.h"
#include "FleetManager.h"
#include "GameShip.h"
#include "Abilities.h"
#include "AbilityManager.h"

int main(){
    std::vector<int> shipSizes = {2, 3, 4};
    FleetManager shipManager(3, shipSizes);
    int fieldWidth = 10;
    int fieldHeight = 10;
    AbilityManager abilityManager;
    GameShip GameShip(fieldWidth, fieldHeight, abilityManager);
    GameShip.plotField();
    std::cout<<"all is ok"<<std::endl;
    Ship n_s;
    n_s.set_orientation(Ship::Orientation::Horizontal);
    n_s.set_length(3);
    std::pair<int, int> coordinat = std::make_pair(1,1);
    Ship* pns = &n_s;
    GameShip.setShip(pns,coordinat, pns->orientation);
    GameShip.attackCell(1,1);
    abilityManager.useAbility(GameShip);
    std::cout<<"all is ok"<<std::endl;
    GameShip.plotField();
    std::cout<<"all is ok"<<std::endl;
    abilityManager.useAbility(GameShip);
    std::cout<<"all is ok"<<std::endl;
    abilityManager.useAbility(GameShip);
    std::cout<<"all is ok"<<std::endl;
    GameShip.attackCell(-2,1);
    GameShip.plotField();
    std::cout<<"all is ok"<<std::endl;

    return 0;
}
