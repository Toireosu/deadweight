#pragma once

#include "core/transformable.hpp"

class RenderableBase : public Transformable {
public:
    virtual void render() = 0;
};