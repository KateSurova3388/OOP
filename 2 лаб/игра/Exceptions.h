#ifndef EXCEPTIONS_H  
#define EXCEPTIONS_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

#include "GameShip.h"
#include "AbilityManager.h"

class AbilityException : public std::runtime_error {
public:
    explicit AbilityException (const std::string& message);
};

class BoundsException : public std::runtime_error {
public:
    explicit BoundsException (const std::string& message);
};

class OverlappingShipsException : public std::runtime_error {
public:
    explicit OverlappingShipsException (const std::string& message);
};

#endif