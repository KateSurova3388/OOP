cmake_minimum_required(VERSION 3.28)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP main.cpp
        Ship.cpp
        Ship.h
        SegmentState.h
        ShipManager.cpp
        ShipManager.h
        GameBoard.cpp
        GameBoard.h
        IAbility.cpp
        IAbility.h
        CellState.cpp
        CellState.h
        AbilityManager.cpp
        AbilityManager.h
        DoubleDamageAbility.cpp
        DoubleDamageAbility.h
        ScannerAbility.cpp
        ScannerAbility.h
        BombingAbility.cpp
        BombingAbility.h
        AttackOutOfRangeError.cpp
        AttackOutOfRangeError.h
        NullAbilityUseError.cpp
        NullAbilityUseError.h
        LocationShipError.cpp
        LocationShipError.h
        Game.cpp
        Game.h
        NonNumberInputError.cpp
        NonNumberInputError.h
        GameState.cpp
        GameState.h
        FileInteractionError.cpp
        FileInteractionError.h
)
