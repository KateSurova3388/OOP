#include "AbilityManager.h"

int AbilityManager::generateRandomNumber(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(1, 3);
    return dist(g);
}



AbilityManager::AbilityManager() {
    std::vector<int> indexes;
    indexes.push_back(0);
    indexes.push_back(1);
    indexes.push_back(2);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexes.begin(), indexes.end(), g);
    
    for (auto& ability_idx : indexes) {
        abilityQueue.push(ability_idx); 
    }
}

AbilityManager::~AbilityManager(){

}

std::unique_ptr<Ability> AbilityManager::getAbility(int idx){
    switch (idx) {
        case 0:
            return std::make_unique<DoubleDamage>();
        case 1:
            return std::make_unique<Scanner>();
        case 2:
            return std::make_unique<Bombardment>();
        default:
            return nullptr;
    }
}

void AbilityManager::addAbilityIdx(int idx){
    abilityQueue.push(idx);
}

void AbilityManager::useAbility(GameShip& GameShip){
    if (!abilityQueue.empty()) {
            auto ability_idx = abilityQueue.front(); 
            std::unique_ptr<Ability> ability = getAbility(ability_idx); 
            ability->ability(GameShip);
            abilityQueue.pop(); 
        } else {
            // std::cout << "No abilities left!" << std::endl;
            throw AbilityException("Нет возможностей к использованию.");
        }
}

