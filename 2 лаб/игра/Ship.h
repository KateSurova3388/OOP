#ifndef SHIP_H  
#define SHIP_H 
#include <iostream>
#include <vector>
#include <stdexcept>

class Ship{
private:
    enum class Condition { Intact, Damaged, Destroyed };
    int length;
    std::vector<Condition> conditionArray;

public:
    enum class Orientation { Horizontal, Vertical };
    Orientation orientation;

    void set_length(int length);
    void set_orientation(Orientation orientation);
    int get_length() const;
    void damage(int segment);
    bool isDead();
};
#endif