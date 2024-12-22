#include <iostream>
#include <vector>
#include <limits>
#include "GameShip.h"
#include "manager.hpp"

using namespace std;

int main() {
    int m = 10;
    int n = 10;

    GameShip field(n, m);

    // Используем Manager для создания кораблей
    std::initializer_list<std::pair<size_t, bool>> shipData = {{3, true}, {4, false}};
    Manager manager(shipData.size(), shipData);
    std::vector<Ship> ships = manager.get_ships();

    int x, y, orientation;

    for (size_t i = 0; i < ships.size(); i++) {
        bool placed = false;

        while (!placed) {
            cout << "Input coordinates and orientation for ship " << i + 1 << " (x y o [0-Horizontal, 1-Vertical]): ";
            cin >> x >> y >> orientation;

            if (cin.fail() || x < 0 || y < 0 || orientation < 0 || orientation > 1) {
                cout << "Invalid input! Please enter positive integers for x, y, and 0 or 1 for orientation." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (orientation == 0) {
                ships[i] = Ship(ships[i].size(), Ship::Orientation::Horizontal);
            } else {
                ships[i] = Ship(ships[i].size(), Ship::Orientation::Vertical);
            }

            try {
                field.placeShip(x, y, ships[i]);
                placed = true;
            } catch (const std::invalid_argument& e) {
                cout << e.what() << endl;
            }
        }
    }

    field.plotField();

    int x1, y1;
    cout << "Enter attack coordinates (x y): ";
    cin >> x1 >> y1;

    try {
        field.attackCell(x1, y1);
    } catch (const std::out_of_range& e) {
        cout << e.what() << endl;
    }

    field.plotField();

    return 0;
}
