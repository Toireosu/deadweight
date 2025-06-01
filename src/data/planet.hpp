#pragma once

#include "world.hpp" 
#include <raylib.h>

class Planet : public World {
private:
    std::string _brief;
    unsigned long long _population;
    // Measured in 10^3 km
    float _diameter;
    // Temp
    Color _color;
public: 
    Planet(std::string name, Faction* faction, SpaceCoords coords, std::string brief, unsigned long long population, float diameter, Color color) : World(name, faction, coords) {
        _brief = brief;
        _population = population;
        _diameter = diameter;
        _color = color;
    }

    std::string getBrief() { return _brief; }
    unsigned long long getPopulation() { return _population; };
    // Measured in 10^3 km
    float getDiameter() { return _diameter; };
    Color getColor() { return _color; };

    std::string scan() override {
        return _brief;
    } 
};