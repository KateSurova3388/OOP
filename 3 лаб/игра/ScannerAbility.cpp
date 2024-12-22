

#include "ScannerAbility.h"
#include <iostream>
void ScannerAbility::useAbility() {
    std::cout << "Scanner is active, type cords:\n";
    int x, y;
    std::cin >> x >> y;
    if(gameBoard->isSegmentInCell(x,y) || gameBoard->isSegmentInCell(x+1,y) || gameBoard->isSegmentInCell(x,y-1) || gameBoard->isSegmentInCell(x-1,y-1))
    {
      std::cout << "Ship in area!\n";
    }
    else
    {
        std::cout << "No ships in area!\n";
    }
}

ScannerAbility::ScannerAbility(GameBoard *gameBoard): gameBoard(gameBoard) {
    this->label = "Scanner";
}


