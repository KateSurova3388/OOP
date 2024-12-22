

#ifndef OOP_NULLABILITYUSEERROR_H
#define OOP_NULLABILITYUSEERROR_H
#include <iostream>

class NullAbilityUseError: public std::runtime_error{
public:
    NullAbilityUseError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //OOP_NULLABILITYUSEERROR_H
