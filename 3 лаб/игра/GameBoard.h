#ifndef OOP_GAMEBOARD_H
#define OOP_GAMEBOARD_H
#include <iostream>
#include "Ship.h"
#include "CellState.h"
#include "ShipManager.h"
#include "AttackOutOfRangeError.h"
#include "LocationShipError.h"
class GameBoard{
private:
    int fieldWidth;
    int fieldHeight;
    int** field;
    CellState** exploredField;



public:
    GameBoard(int width, int height);
    GameBoard(const GameBoard& other);
    GameBoard& operator=(const GameBoard& other);
    GameBoard(GameBoard&& other) noexcept ;
    GameBoard& operator=(GameBoard&& other);
    ~GameBoard();
    bool attackCell(int x,int y,ShipManager* shipManager,bool isDoubleDamage = false);
    void printField();
    void setShips(ShipManager* shipManager);
    void addShip(Ship* ship, int x, int y, bool isHorizontal,int index);
    bool isSegmentInCell(int x,int y);
    void printMap(ShipManager* shipManager);
    std::string getFieldLine(int lineIndex);
    std::string getMapLine(int lineIndex,ShipManager* shipManager);
    void printOpenMap(ShipManager* shipManager);
    int getWidth() const;
    int getHeight() const;
    void resetField();
    void loadField(int** newField);
    void loadMap(CellState** newExploredField);

};
#endif
