#pragma once

#include "core/transformable.hpp"
#include "core/updatable.hpp"

class RenderableBase : public Transformable, public Updatable {
public:
    virtual void render() = 0;
};