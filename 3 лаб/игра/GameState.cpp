
#include <fstream>

#include <sstream>

#include <filesystem>
#include "GameState.h"



std::ostream &operator<<(std::ostream &out, const GameState &state) {
    std::cout << "Begin save\n";
    out << "Game Settings\n";
    out << std::to_string(state.boardWidth) + " " + std::to_string(state.boardHeight)+ " " + std::to_string(state.shipSizes.size())+"\n";
    out << "Player ships\n";
    for (int i = 0; i < state.shipSizes.size(); ++i) {
        out << state.playerShipManager->getShipInfoStr(i);
    }
    out << "Computer Ships\n";
    for (int i = 0; i < state.shipSizes.size(); ++i) {
        out << state.computerShipManager->getShipInfoStr(i);
    }
    out << "Player map\n";
    for (int i = 0; i < state.boardHeight; ++i) {
        out << state.playerGameBoard->getMapLine(i,state.playerShipManager);
    }
    out << "Player field\n";
    for (int i = 0; i < state.boardHeight; ++i) {
        out << state.playerGameBoard->getFieldLine(i);
    }
    out<<"Computer map\n";
    for (int i = 0; i < state.boardHeight; ++i) {
        out << state.computerGameBoard->getMapLine(i,state.computerShipManager);
    }
    out << "Computer field\n";
    for (int i = 0; i < state.boardHeight; ++i) {
        out << state.computerGameBoard->getFieldLine(i);
    }
    out << "Ability\n";
    out << state.abilityManager->getLen() << "\n";
    out << state.abilityManager->getAbilityStr();




    return out;
}

std::istream &operator>>(std::istream &in, GameState &state) {
    std::string line;

    std::getline(in, line);
    in >> state.boardWidth >> state.boardHeight >> state.shipCount;
    in.ignore();

    std::getline(in, line);
    state.shipSizes.clear();
    std::vector<Ship*> tempPlayerShips;
    for (int i = 0; i < state.shipCount; ++i) {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);
        state.shipSizes.push_back(std::stoi(splitLine[0]));

        Ship* tempShip = new Ship(std::stoi(splitLine[0]));
        tempShip->setPosition(std::stoi(splitLine[1]),std::stoi(splitLine[2]),std::stoi(splitLine[3]));

        std::vector<SegmentState> tempSegments;
        for (int j = 0; j < std::stoi(splitLine[0]); ++j) {
            switch (splitLine[4][j]) {
                case '0':
                    tempSegments.push_back(SegmentState::Intact);
                    break;
                case '1':
                    tempSegments.push_back(SegmentState::Damaged);
                    break;
                case '2':
                    tempSegments.push_back(SegmentState::Destroyed);
                    break;
                default:
                    throw FileInteractionError("Wrong map format\n");
            }
        }
        
        tempShip->setSegmentsStates(tempSegments);
        tempPlayerShips.push_back(tempShip);
    }

    std::getline(in, line);

    std::vector<Ship*> tempComputerShips;
    for (int i = 0; i < state.shipCount; ++i) {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);


        Ship* tempShip = new Ship(std::stoi(splitLine[0]));
        tempShip->setPosition(std::stoi(splitLine[1]),std::stoi(splitLine[2]),std::stoi(splitLine[3]));

        std::vector<SegmentState> tempSegments;
        for (int j = 0; j < std::stoi(splitLine[0]); ++j) {
            switch (splitLine[4][j]) {
                case '0':
                    tempSegments.push_back(SegmentState::Intact);
                    break;
                case '1':
                    tempSegments.push_back(SegmentState::Damaged);
                    break;
                case '2':
                    tempSegments.push_back(SegmentState::Destroyed);
                    break;
                default:
                    throw 321;
            }
        }

        tempShip->setSegmentsStates(tempSegments);
        tempComputerShips.push_back(tempShip);
    }

    delete state.playerShipManager;
    delete state.computerShipManager;

    state.playerShipManager = new ShipManager(state.shipSizes);
    state.computerShipManager = new ShipManager(state.shipSizes);

    state.playerShipManager->resetShips(tempPlayerShips);
    state.computerShipManager->resetShips(tempComputerShips);

    std::getline(in, line);

    int** tempPlayerField = new int*[state.boardHeight];
    CellState** tempPlayerExploredField = new CellState*[state.boardHeight];
    for (int i = 0; i < state.boardHeight; ++i) {
        tempPlayerField[i] = new int[state.boardWidth];
        tempPlayerExploredField[i] = new CellState[state.boardWidth];
    }

    for (int i = 0; i < state.boardHeight; ++i) {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);
        for (int j = 0; j < state.boardWidth; ++j) {
            switch (std::stoi(splitLine[j])) {
                case 0:
                    tempPlayerExploredField[i][j] = CellState::Unknown;
                    break;
                case 1:
                    tempPlayerExploredField[i][j] = CellState::Nothing;
                    break;
                case 2:
                    tempPlayerExploredField[i][j] = CellState::Ship;
                    break;
                default:
                    throw FileInteractionError("Wrong map format\n");
            }
        }
    }

    std::getline(in, line);

    for (int i = 0; i < state.boardHeight; ++i)
    {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);
        for (int j = 0; j < state.boardWidth; ++j)
        {
            tempPlayerField[i][j] = std::stoi(splitLine[j]);
        }

    }

    delete state.playerGameBoard;
    state.playerGameBoard = new GameBoard(state.boardWidth,state.boardHeight);
    state.playerGameBoard->loadMap(tempPlayerExploredField);
    state.playerGameBoard->loadField(tempPlayerField);

    std::getline(in, line);

    int** tempComputerField = new int*[state.boardHeight];
    CellState** tempComputerExploredField = new CellState*[state.boardHeight];
    for (int i = 0; i < state.boardHeight; ++i) {
        tempComputerField[i] = new int[state.boardWidth];
        tempComputerExploredField[i] = new CellState[state.boardWidth];
    }

    for (int i = 0; i < state.boardHeight; ++i) {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);
        for (int j = 0; j < state.boardWidth; ++j) {
            switch (std::stoi(splitLine[j])) {
                case 0:
                    tempComputerExploredField[i][j] = CellState::Unknown;
                    break;
                case 1:
                    tempComputerExploredField[i][j] = CellState::Nothing;
                    break;
                case 2:
                    tempComputerExploredField[i][j] = CellState::Ship;
                    break;
                default:
                    throw 123;
            }
        }
    }

    std::getline(in, line);

    for (int i = 0; i < state.boardHeight; ++i)
    {
        std::getline(in, line);
        std::vector<std::string> splitLine = state.splitString(line);
        for (int j = 0; j < state.boardWidth; ++j)
        {
            tempComputerField[i][j] = std::stoi(splitLine[j]);
        }

    }

    delete state.computerGameBoard;
    state.computerGameBoard = new GameBoard(state.boardWidth,state.boardHeight);
    state.computerGameBoard->loadMap(tempComputerExploredField);
    state.computerGameBoard->loadField(tempComputerField);

    std::getline(in, line);
    int abilityCount;

    in >> abilityCount;
    in.ignore();
    std::getline(in, line);
    std::vector<std::string> splitLine = state.splitString(line);
    state.abilityManager->loadAbility(splitLine);
    state.abilityManager->setNewFields(state.computerGameBoard,state.computerShipManager);

    return in;
}

void GameState::saveGame(const std::string& fileName) const {

    if (!std::filesystem::exists("../saves/")) {
        throw FileInteractionError("Directory ../saves/ does not exist.\n");
    }

    std::ofstream fileToWrite("../saves/"+fileName + ".txt");
    if (!fileToWrite.is_open()) {
        throw FileInteractionError("File open error " + fileName+".txt\n");
    }


    fileToWrite << *this;

    fileToWrite.close();
}

void GameState::loadGame(const std::string& fileName) {
    if (!std::filesystem::exists("../saves/")) {
        throw FileInteractionError("Directory ../saves/ does not exist.\n");
    }

    std::ifstream fileToRead("../saves/" + fileName + ".txt");
    if (!fileToRead.is_open()) {
        throw FileInteractionError("File open error " + fileName+".txt\n");
    }

    fileToRead >> *this;

    fileToRead.close();
}


std::vector<std::string>  GameState::splitString(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}




