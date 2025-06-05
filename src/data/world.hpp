#pragma once

#include <string>
#include "data/faction.hpp"
#include "data/space_coords.hpp"

#include <vector>
#include <memory>

class Job;
class World {
protected:
    std::string _name;
    Faction* _faction; 
    SpaceCoords _coords;
public:

    World(std::string name, Faction* faction, SpaceCoords coords) {
        _name = name;
        _faction = faction;
        _coords = coords;
    }

    virtual std::string getBrief() = 0;
    std::string getName() { return _name; };
    Faction* getFaction() { return _faction; }; 
    SpaceCoords getCoords() { return _coords; }

    virtual std::string scan() = 0;

    std::vector<std::shared_ptr<Job>> fetchJobs();
};
