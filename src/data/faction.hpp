#pragma once

#include <string>

class Faction {
protected:
    std::string _name;
    std::string _acronym;
public:
    Faction(std::string name, std::string acronym) {
        _name = name;
        _acronym = acronym;
    }
    std::string getName() { return _name; }
    std::string getAcronym() { return _acronym; }
};