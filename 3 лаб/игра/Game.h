
#ifndef OOP_GAME_H
#define OOP_GAME_H
#include "GameBoard.h"
#include "AbilityManager.h"
#include "NullAbilityUseError.h"
#include "NonNumberInputError.h"
#include "GameState.h"


class Game {

    GameState* gameState;

    void setPlayerShips();
    void setComputerShips();
    void startRoundCycle();
    void playerAttack();
    void computerAttack();
    void clearPlayerMemory();
    void clearComputerMemory();
    void nextTurn();
    void initComputer();
    void initNewGame();
    void continueGame();
    void startGameCycle(bool isSave);


public:
    void play();
    Game(int width, int height,std::vector<int> sizes);
    ~Game();
};


#endif //OOP_GAME_H
