
#ifndef OOP_NONNUMBERINPUTERROR_H
#define OOP_NONNUMBERINPUTERROR_H

#include <iostream>

class NonNumberInputError: public std::runtime_error {
public:
    NonNumberInputError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //OOP_NONNUMBERINPUTERROR_H
