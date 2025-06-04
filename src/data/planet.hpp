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
    Texture* _texture;

    void generateTexture(Color color) {
        Image image = GenImagePerlinNoise(64, 64, _name.size() * 10, _brief.size() * 4, 4.0f);
        _texture = new Texture(LoadTextureFromImage(image));
        UnloadImage(image);
    };
public: 
    Planet(std::string name, Faction* faction, SpaceCoords coords, std::string brief, unsigned long long population, float diameter, Color color) : World(name, faction, coords) {
        _brief = brief;
        _population = population;
        _diameter = diameter;
        _color = color;
        generateTexture(color);
    }

    ~Planet() {
        UnloadTexture(*_texture);
        delete _texture;
    }

    std::string getBrief() { return _brief; }
    unsigned long long getPopulation() { return _population; };
    // Measured in 10^3 km
    float getDiameter() { return _diameter; };
    Color getColor() { return _color; };
    Texture* getTexture() { return _texture; }

    std::string scan() override {
        return _brief;
    } 
};