//
// Created by 96919 on 16.10.2024.
//

#ifndef OOP_ATTACKOUTOFRANGEERROR_H
#define OOP_ATTACKOUTOFRANGEERROR_H
#include <iostream>

class AttackOutOfRangeError :  public std::runtime_error {
public:
    AttackOutOfRangeError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //OOP_ATTACKOUTOFRANGEERROR_H
