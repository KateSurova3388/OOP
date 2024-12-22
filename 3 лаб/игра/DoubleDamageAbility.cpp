

#include "DoubleDamageAbility.h"
#include <iostream>
void DoubleDamageAbility::useAbility() {
    std::cout << "Double damage is active\n";
    this->isDoubleDamage = true;

}

DoubleDamageAbility::DoubleDamageAbility(bool &isDoubleDamage):isDoubleDamage(isDoubleDamage) {
    this->label="DoubleDamage";
}
