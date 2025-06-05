#pragma once

#include <string>

#include "data/world.hpp"
#include <sstream>

enum StorableType {
    GRAIN,
    ORE,
    WEAPONS,
    PERSONEL,
    CHEMICALS,
    ELECTRONICS
};  

class Storable {
private:
    StorableType _type;
    std::string _name;
    World* _origin;
    std::string _questTag;
    // In kg
    float _mass;
public:
    Storable(StorableType type, std::string name, World* origin, float mass) {
        _type = type;
        _name = name;
        _origin = origin;
        _mass = mass;
    }

    StorableType getType() { return _type; }
    std::string getName() { return _name; }
    std::string getQuestTag() { return _questTag; }
    World* getOrigin() { return _origin; }
    float getMass() { return _mass; }
};