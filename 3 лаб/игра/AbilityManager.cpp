
#include "AbilityManager.h"
#include "NullAbilityUseError.h"

AbilityManager::AbilityManager(bool &isDoubleDamage,GameBoard* gameBoard,ShipManager* shipManager):isDoubleDamage(isDoubleDamage),gameBoard(gameBoard),shipManager(shipManager) {
    std::vector<std::shared_ptr<IAbility>> tempVec;
    tempVec.push_back(std::make_shared<DoubleDamageAbility>(isDoubleDamage));
    tempVec.push_back(std::make_shared<ScannerAbility>(gameBoard));
    tempVec.push_back(std::make_shared<BombingAbility>(isDoubleDamage,shipManager));


    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(tempVec.begin(), tempVec.end(), g);


    for (auto &ability: tempVec) {
        this->abilityQueue.push_back(ability);
    }


}



AbilityManager::~AbilityManager() {
    this->abilityQueue.clear();
}

void AbilityManager::useNextAbility() {
    if (abilityQueue.empty())
    {
        throw NullAbilityUseError("There are no available abilities\n");
    }

    abilityQueue[0]->useAbility();
    this->abilityQueue.erase(abilityQueue.begin());
}

void AbilityManager::addRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);

    int randomClass = dis(gen);
    switch (randomClass) {
        case 1:
            abilityQueue.push_back(std::make_shared<DoubleDamageAbility>(isDoubleDamage));
            break;
        case 2:
            abilityQueue.push_back(std::make_shared<ScannerAbility>(gameBoard));
            break;
        case 3:
            abilityQueue.push_back(std::make_shared<BombingAbility>(isDoubleDamage,shipManager));
            break;
        default:
            std::cerr << "Unexpected random class number" << std::endl;
            break;
    }
}

int AbilityManager::getLen() {
    return this->abilityQueue.size();
}

std::string AbilityManager::getTopLabel() {
    return this->abilityQueue[0]->getLabel();
}



void AbilityManager::setNewFields(GameBoard *gameBoard, ShipManager *shipManager) {
    this->gameBoard = gameBoard;
    this->shipManager = shipManager;

    std::vector<std::shared_ptr<IAbility>> tempVec;
    for (const auto & i : abilityQueue) {
        tempVec.push_back(i);
    }
    abilityQueue.clear();

    for (int i = tempVec.size()-1;i>=0;i--) {
        if (auto doubleDamageAbility = std::dynamic_pointer_cast<DoubleDamageAbility>(tempVec[i])) {
            abilityQueue.push_back(std::make_shared<DoubleDamageAbility>(isDoubleDamage));
        } else if (auto scannerAbility = std::dynamic_pointer_cast<ScannerAbility>(tempVec[i])) {
            abilityQueue.push_back(std::make_shared<ScannerAbility>(gameBoard));
        } else if (auto bombingAbility = std::dynamic_pointer_cast<BombingAbility>(tempVec[i])) {
            abilityQueue.push_back(std::make_shared<BombingAbility>(isDoubleDamage, shipManager));
        }
    }

}

std::string AbilityManager::getAbilityStr() {
    std::string msg = "";



    for (auto ability:abilityQueue) {
        msg+= ability->getLabel();
        msg+=" ";
    }
    return msg;
}

void AbilityManager::loadAbility(std::vector<std::string> newAbility) {

        this->abilityQueue.clear();

    for (int i = newAbility.size()-1;i>=0;i--)
    {
        if(newAbility[i] == "DoubleDamage")
        {
            abilityQueue.push_back(std::make_shared<DoubleDamageAbility>(isDoubleDamage));
        }
        else if(newAbility[i] == "Scanner")
        {
            abilityQueue.push_back(std::make_shared<ScannerAbility>(gameBoard));
        } else
        {
            abilityQueue.push_back(std::make_shared<BombingAbility>(isDoubleDamage,shipManager));
        }
    }
    for (const auto& ability:abilityQueue)
    {
        std::cout << ability->getLabel();
    }
}

