//
// Created by 96919 on 15.10.2024.
//

#ifndef OOP_DOUBLEDAMAGEABILITY_H
#define OOP_DOUBLEDAMAGEABILITY_H
#include "IAbility.h"

class DoubleDamageAbility:public IAbility {
    bool &isDoubleDamage;
    void useAbility() override;
public:
    DoubleDamageAbility(bool& isDoubleDamage);
};


#endif //OOP_DOUBLEDAMAGEABILITY_H
