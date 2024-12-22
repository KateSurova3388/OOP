#include "GameShip.h"

GameShip::GameShip(int width, int height, AbilityManager& abilityManager) : 
    abilityManager(abilityManager) {  // Initialize reference
    if ((width <= 0) || (height <= 0)) {
        throw BoundsException("Invalid values: width & height must be more than 0.");
    }
    this->height = height;
    this->width = width;
    doubleDamage = false;
    Field.resize(width, std::vector<CellStatus>(height, CellStatus::Unknown));
    ShipCoordinates.resize(height, std::vector<std::pair<Ship*, int>>(width, { nullptr, -1 }));
}

GameShip::~GameShip() {
    // No need for special cleanup for references
}

void GameShip::setShip(Ship* ship, const std::pair<int, int>& coordinates, Ship::Orientation orientation) {
    ship->set_orientation(orientation);
    int shipLength = ship->get_length();

    int y = coordinates.first;
    int x = coordinates.second;

    int dx = (orientation == Ship::Orientation::Horizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::Vertical) ? 1 : 0;

    if (canPlaceShip(ship, x, y, dx, dy)) {
        for (int i = 0; i < shipLength; i++) {
            int newY = y + dy * i;
            int newX = x + dx * i;

            if (newY < 0 || newY >= ShipCoordinates.size() || 
                newX < 0 || newX >= ShipCoordinates[0].size()) {
                std::cerr << "Error: Ship placement goes out of bounds." << std::endl;
                return; 
            }

            ShipCoordinates[newY][newX].first = ship;
            ShipCoordinates[newY][newX].second = i;
            Field[newY][newX] = CellStatus::Occupied;
        }
    }
}

bool GameShip::CheckShipCondition(Ship* ship) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (ShipCoordinates[y][x].first == ship && ShipCoordinates[y][x].first->isDead() == false) {
                return false;
            }
        }
    }
    return true;
}
    
void GameShip::attackCell(int y, int x) {
    if (x <0 || y < 0 || x >= width || y >= height){
        throw BoundsException("Invalid values: width & height must be more than 0.");
    }
    if (Field[y][x] == CellStatus::Occupied) {
        Ship* shipToAttack = ShipCoordinates[y][x].first;
        if (doubleDamage == true) {
            shipToAttack->damage(ShipCoordinates[y][x].second);
            shipToAttack->damage(ShipCoordinates[y][x].second);
            Field[y][x] = CellStatus::Destroyed;
            setDoubleDamage(false);
            if (CheckShipCondition(ShipCoordinates[y][x].first)) {
                generateAbilityIdx(abilityManager);
            }
        } else {
            shipToAttack->damage(ShipCoordinates[y][x].second);
            if (Field[y][x] == CellStatus::Damaged) {
                Field[y][x] = CellStatus::Destroyed;
            } else {
                Field[y][x] = CellStatus::Damaged;
                if (CheckShipCondition(ShipCoordinates[y][x].first)) {
                    generateAbilityIdx(abilityManager);
                }
            }
        } 
    } else {
        if (Field[y][x] == CellStatus::Unknown && ShipCoordinates[y][x].second == -1) {
            Field[y][x] = CellStatus::Empty;
        }
    }
}

bool GameShip::canPlaceShip(Ship* ship, int x, int y, int dx, int dy) {
    int shipLength = ship->get_length();            

    for (int i = 0; i < shipLength; i++) {
        if ((y + dy * i >= height) || (x + dx * i >= width) || (x < 0) || (y < 0)) {
            // std::cout << "Invalid Coords." << "\n";
            // return false;
            throw OverlappingShipsException("Корабли пересекаются, расположены вплотную, или размещение нарушает границы поля.");
        } else if (Field[y + dy * i][x + dx * i] == CellStatus::Occupied) {
            // std::cout << "There is already a ship.";
            // return false;
            throw OverlappingShipsException("Корабли пересекаются, расположены вплотную, или размещение нарушает границы поля.");
        }
    }
    return true;
}

void GameShip::plotField() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            switch (Field[x][y]) {
                case CellStatus::Empty:
                    std::cout << ". ";
                    break;
                case CellStatus::Unknown:
                    std::cout << "~ ";
                    break;
                case CellStatus::Occupied:
                    std::cout << "X ";
                    break;
                case CellStatus::Damaged:
                    std::cout << "x ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

// Copy assignment operator
GameShip& GameShip::operator=(const GameShip& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        abilityManager = other.abilityManager;  // No change needed for reference
        Field = other.Field;
        ShipCoordinates = other.ShipCoordinates;
    }
    return *this;
}

// Move constructor
GameShip::GameShip(GameShip&& other) noexcept : 
    width(other.width), height(other.height), 
    Field(std::move(other.Field)), 
    abilityManager(other.abilityManager) { // No change needed for reference
    other.width = 0;
    other.height = 0;
}

// Move assignment operator
GameShip& GameShip::operator=(GameShip&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        abilityManager = other.abilityManager;  // No change needed for reference
        Field = std::move(other.Field);
        ShipCoordinates = std::move(other.ShipCoordinates);
    }
    return *this;
}

void GameShip::getOnlyOccupiedCells() {
    occupiedCells.clear();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (Field[y][x] == CellStatus::Occupied) {
                occupiedCells.emplace_back(y, x);
            }
        }
    }
}

void GameShip::randomBombardment() {
    getOnlyOccupiedCells();
    if (!occupiedCells.empty()) {
        std::uniform_int_distribution<int> dist(0, occupiedCells.size() - 1);
        std::random_device rd;
        std::mt19937 gen(rd());
        
        int randomIndex = dist(gen);
        int y = occupiedCells[randomIndex].first;
        int x = occupiedCells[randomIndex].second;

        Ship* shipToAttack = ShipCoordinates[y][x].first;
        int segmentIndex = ShipCoordinates[y][x].second;
        shipToAttack->damage(segmentIndex);
    } else {
        std::cout << "No ships to bombard." << std::endl;
    }
}

void GameShip::scanArea() {
    int x0, y0;
    std::cout << "Введите координаты левой верхней клетки квадрата сканирования: ";
    std::cin >> x0 >> y0;
    if (x0 == Field[0].size() && y0 == Field[0].size()) {
        x0 -= 1; 
        y0 -= 1;
    } else if (x0 == Field[0].size() && y0 != Field.size()) {
        x0 -= 1;
    } else if (x0 != Field[0].size() && y0 == Field.size()) {
        y0 -= 1;
    }

    // Make cell left-up if user is invalid
    if ((ShipCoordinates[x0][y0].second == -1) && 
        (ShipCoordinates[x0 + 1][y0].second == -1) &&
        (ShipCoordinates[x0][y0 + 1].second == -1) && 
        (ShipCoordinates[x0 + 1][y0 + 1].second == -1)) {
        std::cout << "No ships detected." << std::endl;
    } else {
        std::cout << "Ship or ships detected." << std::endl;
    }
}

void GameShip::setDoubleDamage(bool status) {
    doubleDamage = status;
}

void GameShip::generateAbilityIdx(AbilityManager& abilityManager) {
    int randomAbilityIdx = std::rand() % 3;
    abilityManager.addAbilityIdx(randomAbilityIdx);
}
