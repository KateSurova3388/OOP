#ifndef GAMESHIP_H
#define GAMESHIP_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "ship.hpp"



class GameShip {
public:
    enum class CellState { Unknown, Empty, Occupied, Damaged };

    GameShip(size_t rows, size_t cols);
    ~GameShip();

    void placeShip(size_t x, size_t y, Ship& ship);
    void attackCell(size_t x, size_t y);
    void plotField() const;
    
private:
    size_t width;
    size_t height;

    struct Cell {
        Cell& attackCell(size_t x, size_t y);

        CellState state;
        Ship* ship;
        int index;

        Cell() : state(CellState::Unknown), ship(nullptr), index(-1) {}
        bool isEmpty() const { return ship == nullptr; }
    };

    std::vector<std::vector<Cell>> grid;

    bool canPlaceShip(size_t x, size_t y, size_t shipLength, Ship::Orientation orientation) const;
};

#endif
