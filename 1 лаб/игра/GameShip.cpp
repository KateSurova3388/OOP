#include "GameShip.h"

GameShip::GameShip(size_t rows, size_t cols) : height(rows), width(cols) {
    grid.resize(height, std::vector<Cell>(width));
}

GameShip::~GameShip() = default;

void GameShip::placeShip(size_t x, size_t y, Ship& ship) {
    size_t shipLength = ship.size();
    Ship::Orientation orientation = ship.get_orientation();

    if (!canPlaceShip(x, y, shipLength, orientation)) {
        throw std::invalid_argument("Invalid ship placement: Ship goes out of bounds or overlaps with another ship.");
    }

    for (size_t i = 0; i < shipLength; ++i) {
        if (orientation == Ship::Orientation::Horizontal) {
            grid[y][x + i].state = CellState::Occupied;
            grid[y][x + i].ship = &ship;
            grid[y][x + i].index = i;
        } else {
            grid[y + i][x].state = CellState::Occupied;
            grid[y + i][x].ship = &ship;
            grid[y + i][x].index = i;
        }
    }
}

bool GameShip::canPlaceShip(size_t x, size_t y, size_t shipLength, Ship::Orientation orientation) const {
    for (size_t i = 0; i < shipLength; ++i) {
        size_t newX = (orientation == Ship::Orientation::Horizontal) ? x + i : x;
        size_t newY = (orientation == Ship::Orientation::Vertical) ? y + i : y;

        if (newX >= width || newY >= height || grid[newY][newX].state == CellState::Occupied) {
            return false;
        }
    }
    return true;
}

void GameShip::attackCell(size_t x, size_t y) {
    if (x >= width || y >= height) {
        throw std::out_of_range("Invalid coordinates for attack: Out of bounds.");
    }

    Cell& cell = grid[y][x];

    if (cell.state == CellState::Occupied && cell.ship) {
        cell.ship->set_state(cell.index);
        cell.state = CellState::Damaged;
        std::cout << "Hit at (" << x << ", " << y << ")!" << std::endl;
    } else {
        cell.state = CellState::Empty;
        std::cout << "Miss at (" << x << ", " << y << ")." << std::endl;
    }
}

void GameShip::plotField() const {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            switch (grid[y][x].state) {
                case CellState::Empty:
                    std::cout << ". ";
                    break;
                case CellState::Unknown:
                    std::cout << "~ ";
                    break;
                case CellState::Occupied:
                    std::cout << "о ";
                    break;
                case CellState::Damaged:
                    std::cout << "X ";
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}
