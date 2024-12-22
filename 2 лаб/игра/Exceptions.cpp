#include "Exceptions.h"

AbilityException::AbilityException(const std::string& message)
    : std::runtime_error(message) {}

BoundsException::BoundsException(const std::string& message)
    : std::runtime_error(message) {}

OverlappingShipsException::OverlappingShipsException(const std::string& message)
    : std::runtime_error(message) {}

