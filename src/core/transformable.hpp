#pragma once

#include <raylib.h>

class Transformable {
protected:
    Vector3 _position = { 0, 0, 0};
    float _scale = 1.0f;

public:
    Vector3 getPosition() { return _position; }
    void setPosition(Vector3 position) { _position = position; }
    
    float getScale() { return _scale; }
    void setScale(float scale) { _scale = scale; }
};