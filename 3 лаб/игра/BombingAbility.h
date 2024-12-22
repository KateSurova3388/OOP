#ifndef OOP_BOMBINGABILITY_H
#define OOP_BOMBINGABILITY_H
#include "IAbility.h"
#include "GameBoard.h"

class BombingAbility : public IAbility{
    bool &isDoubleDamage;
    ShipManager* shipManager;
    void useAbility() override;
public:
    BombingAbility(bool &isDoubleDamage,ShipManager* shipManager);

};


#endif //OOP_BOMBINGABILITY_H
