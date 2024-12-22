//
// Created by 96919 on 15.10.2024.
//

#ifndef OOP_IABILITY_H
#define OOP_IABILITY_H
#include "GameBoard.h"

class IAbility {
protected:
    std::string label;
public:
    virtual void useAbility() =0;
    virtual ~IAbility() = default;
    std::string getLabel();
};


#endif //OOP_IABILITY_H
