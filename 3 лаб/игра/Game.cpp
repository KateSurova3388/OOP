
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Game.h"

Game::Game(int width, int height,std::vector<int> sizes)  {
    srand(time(0));
    this->gameState = new GameState();
    this->gameState->boardWidth = width;
    this->gameState->boardHeight = height;
    this->gameState->shipSizes = sizes;

    gameState->isPlayerWon = false;




}



void Game::startGameCycle(bool isSave)
{
    if(isSave)
    {
        isSave = false;
        startRoundCycle();
    }
    while(true)
    {
        if (!gameState->isPlayerWon)
        {
            initNewGame();
        }
        else
        {
            continueGame();
        }
        startRoundCycle();
        if (!gameState->isPlayerWon)
        {
            clearPlayerMemory();
        }
        clearComputerMemory();

    }
}



void Game::initNewGame()
{
    initComputer();

    gameState->isPlayerWon = false;
    gameState->isDoubleDamage = false;
    gameState->playerShipManager = new ShipManager(gameState->shipSizes);
    gameState->playerGameBoard = new GameBoard(gameState->boardWidth, gameState->boardHeight);
    gameState->abilityManager = new AbilityManager(gameState->isDoubleDamage,gameState->computerGameBoard,gameState->computerShipManager);


    setPlayerShips();
    setComputerShips();
}


void Game::setPlayerShips() {
    for (int i = 0; i < gameState->playerShipManager->getShipCount(); ++i)
    {
        while(true)
        {
            try
            {
                int x,y;
                int isHorizon;
                std::cout << "Type ship coords and is it horizontal\n";
                std::cin >> x >> y >> isHorizon;


                if (std::cin.fail()) {
                    throw NonNumberInputError("Invalid input. Please enter numbers.\n");
                }

                gameState->playerGameBoard->addShip(gameState->playerShipManager->getShips()[i],x,y,(bool)isHorizon,i);
                break;
            }
            catch(LocationShipError& e)
            {
                std::cout << e.what();
                continue;
            }
            catch (NonNumberInputError& e) {
                std::cout << e.what();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
    }
}

void Game::setComputerShips() {
    for (int i = 0; i < gameState->computerShipManager->getShipCount(); ++i)
    {
        while(true)
        {
            try
            {
                int x = rand() % (gameState->computerGameBoard->getWidth());
                int y = rand() % (gameState->computerGameBoard->getWidth());
                gameState->computerGameBoard->addShip(gameState->computerShipManager->getShips()[i],x,y,(bool)(rand() % 2),i);
                break;
            }
            catch(LocationShipError& e)
            {
                continue;
            }

        }
    }
}

void Game::playerAttack() {
    while(true) {
        try {
            int x,y;
            std::cout << "Type attack coords\n";
            std::cin >> x >> y;

            if (std::cin.fail()) {
                throw NonNumberInputError("Invalid input. Please enter numbers.\n");
            }

            if (gameState->computerGameBoard->attackCell(x, y,gameState->computerShipManager, gameState->isDoubleDamage)) {
                gameState->abilityManager->addRandomAbility();
            }
            gameState->isDoubleDamage = false;
            break;
        }
        catch (AttackOutOfRangeError& e) {
            std::cout << e.what();
            continue;
        }
        catch (NonNumberInputError& e) {
            std::cout << e.what();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}


void Game::startRoundCycle() {
    while (!gameState->computerShipManager->isAllShipDestroyed() && !gameState->playerShipManager->isAllShipDestroyed())
    {
        nextTurn();
    }

    if (gameState->computerShipManager->isAllShipDestroyed())
    {
        std::cout << "Win\n";
        gameState->isPlayerWon = true;
    } else
    {
        std::cout << "Loose\n";

    }
}

void Game::computerAttack() {


    int x = rand() % (gameState->computerGameBoard->getWidth());
    int y = rand() % (gameState->computerGameBoard->getHeight());

    gameState->playerGameBoard->attackCell(x, y, gameState->playerShipManager, false);


}


Game::~Game() {
    this->clearComputerMemory();
    this->clearPlayerMemory();
    delete gameState;
}



void Game::initComputer() {
    gameState->computerGameBoard = new GameBoard(gameState->boardWidth, gameState->boardHeight);
    gameState->computerShipManager = new ShipManager(gameState->shipSizes);
}

void Game::clearPlayerMemory() {
    delete gameState->playerShipManager;
    delete gameState->playerGameBoard;
    delete gameState->abilityManager;
}


void Game::clearComputerMemory() {
    delete gameState->computerShipManager;
    delete gameState->computerGameBoard;
}

void Game::continueGame() {
    gameState->isPlayerWon = false;


    gameState->computerShipManager = new ShipManager(gameState->shipSizes);
    gameState->computerGameBoard = new GameBoard(gameState->boardWidth, gameState->boardHeight);

    gameState->abilityManager->setNewFields(gameState->computerGameBoard,gameState->computerShipManager);
    setComputerShips();
}

void Game::nextTurn() {

    gameState->playerGameBoard->printOpenMap(gameState->playerShipManager);

    std::cout << "--------------------------\n";
    gameState->computerGameBoard->printOpenMap(gameState->computerShipManager);

    gameState->computerGameBoard->printMap(gameState->computerShipManager);
    std::cout << "Available ability: ";
    if(gameState->abilityManager->getLen() == 0)
    {
        std::cout << "None\n";
    }
    else
    {
        std::cout << gameState->abilityManager->getTopLabel() << "\n";
    }
    std::cout << "Attack - 0, Use ability - 1, Save to file - 2, Load from file - 3\n";
    int choose;
    std::cin >> choose;

    switch (choose) {
        case 1:
            try {
                gameState->abilityManager->useNextAbility();
            }
            catch (NullAbilityUseError &e) {
                std::cout << e.what();
            }
            break;
        case 2: {
            std::string fileName;
            std::cout << "Type file name\n";
            std::cin >> fileName;
            gameState->saveGame(fileName);
            return;
                }
        case 3: {
            std::string fileName;
            std::cout << "Type file name\n";
            std::cin >> fileName;

            try
            {
                gameState->loadGame(fileName);
            }
            catch(std::exception& e)
            {
                std::cout << e.what() << "\n";
            }

            return;
        }
        default:
            break;


    }


    playerAttack();



    computerAttack();
}

void Game::play() {
    int chose;
    std::cout << "0 - load game, 1 - start new game\n";
    std::cin >> chose;
    if((bool)chose)
    {
        startGameCycle(false);
    } else
    {
        initComputer();
        gameState->isPlayerWon = false;
        gameState->isDoubleDamage = false;
        gameState->playerShipManager = new ShipManager(gameState->shipSizes);
        gameState->playerGameBoard = new GameBoard(gameState->boardWidth, gameState->boardHeight);
        gameState->abilityManager = new AbilityManager(gameState->isDoubleDamage,gameState->computerGameBoard,gameState->computerShipManager);
        std::string fileName;
        std::cout << "Type file name\n";
        std::cin >> fileName;
        bool isSucceed = true;
        try
        {
            this->gameState->loadGame(fileName);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << "\n";
            isSucceed = false;
        }

        startGameCycle(isSucceed);
    }
}




