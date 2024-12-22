

#ifndef OOP_SCANNERABILITY_H
#define OOP_SCANNERABILITY_H
#include "IAbility.h"

class ScannerAbility: public IAbility{
    GameBoard* gameBoard;
    void useAbility() override;
public:
    ScannerAbility(GameBoard* gameBoard);
};


#endif //OOP_SCANNERABILITY_H
