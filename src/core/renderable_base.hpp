#pragma once

#include "core/transformable.hpp"
#include "core/updatable.hpp"

class RenderableBase : public Transformable, public Updatable {
protected:
    bool _hidden = false;
public:
    bool getHidden() { return _hidden; }
    void setHidden(bool hidden) { _hidden = hidden; }
    virtual void render() = 0;
    void renderCall() {
        if (!getHidden())
            render();
    }
};