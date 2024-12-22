//
// Created by 96919 on 07.11.2024.
//

#ifndef OOP_FILEINTERACTIONERROR_H
#define OOP_FILEINTERACTIONERROR_H
#include <iostream>

class FileInteractionError : public std::runtime_error {
public:
    FileInteractionError(const std::string &msg) : std::runtime_error(msg){};
};


#endif //OOP_FILEINTERACTIONERROR_H
