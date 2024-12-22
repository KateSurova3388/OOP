
#ifndef OOP_LOCATIONSHIPERROR_H
#define OOP_LOCATIONSHIPERROR_H
#include <iostream>

class LocationShipError : public std::runtime_error{
public:
    LocationShipError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //OOP_LOCATIONSHIPERROR_H
