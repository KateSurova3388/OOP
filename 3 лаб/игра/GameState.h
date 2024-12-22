

#ifndef OOP_GAMESTATE_H
#define OOP_GAMESTATE_H
#include "GameBoard.h"
#include "AbilityManager.h"
#include "FileInteractionError.h"

class GameState {
public:
    GameBoard* playerGameBoard;
    GameBoard* computerGameBoard;
    ShipManager* playerShipManager;
    ShipManager* computerShipManager;
    AbilityManager* abilityManager;
    int boardWidth;
    int boardHeight;
    std::vector<int> shipSizes;
    bool isDoubleDamage;
    bool isPlayerWon;
    int shipCount;
    GameState() = default;
    ~GameState() = default;
    friend std::ostream& operator<<(std::ostream& out, const GameState& state);
    friend std::istream& operator>>(std::istream& in, GameState& state);
    void saveGame(const std::string& fileName) const;
    void loadGame(const std::string& filename);
private:
    std::vector<std::string> splitString(const std::string& str);
};


#endif //OOP_GAMESTATE_H
