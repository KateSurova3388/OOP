#ifndef ABILITIES_H  
#define ABILITIES_H 
#include <vector>
#include <stdexcept>

#include "GameShip.h"
#include "AbilityManager.h"
class GameShip;

class Ability{
    friend class AbilityManager;
    public:
        virtual ~Ability();
        virtual void ability(GameShip& GameShip) = 0;
};

class DoubleDamage : public Ability{
        friend class AbilityManager;
public:
       void ability(GameShip& GameShip);
};

class Scanner : public Ability{
        friend class AbilityManager;
public:
        void ability(GameShip& GameShip);
};

class Bombardment : public Ability{
        friend class AbilityManager;
public:
        void ability(GameShip& GameShip);
};
#endif