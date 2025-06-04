#pragma once

#include <raylib.h>

#include "data/planet.hpp"

class StarMapWorld {
private:
    World* _world;
    Vector2 _position;
    Vector2 _labelPosition;
    Vector2 _labelSize; 
    Vector2 _textPosition;
    Vector2 _labelAnchorPoint;
public:
    World* getWorld() { return _world; }
    Vector2 getPosition() { return _position; }
    Vector2 getLabelPosition() { return _labelPosition; }
    Vector2 getTextPosition() { return _textPosition; }
    Vector2 getLabelSize() { return _labelSize; }
    Vector2 getLabelAnchorPoint() { return _labelAnchorPoint; }
    float getRadius() { return ((Planet*)_world)->getDiameter() / 2.0f; }
    StarMapWorld() { }
    StarMapWorld(World* world, Vector2 position, Vector2 labelPosition, Vector2 labelSize, Vector2 textPosition, Vector2 labelAnchorPoint) { 
        _world = world; 
        _position = position; 
        _labelPosition = labelPosition;
        _labelSize = labelSize;
        _textPosition = textPosition;
        _labelAnchorPoint = labelAnchorPoint;
    }
};
