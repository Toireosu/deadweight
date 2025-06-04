#pragma once

#include "renderable_base.hpp"

#include "raylib.h"
#include "raymath.h"

class Renderable3D : public RenderableBase {
protected:
    Model* _model;
public:
    Renderable3D(Model* model) {
        _model = model;
    }
    virtual void render() {
        DrawModel(*_model, _position, _scale, RAYWHITE);
    }
};