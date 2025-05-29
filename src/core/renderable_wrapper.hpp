#pragma once

#include "core/renderable_base.hpp"
#include "core/renderable_UI.hpp"
#include "core/updatable.hpp"
#include <stdexcept>

// Probably mostly for testing purposes 
class RenderableWrapper : public RenderableBase, public Updatable {
private:
    RenderableBase* _real;
public:
    RenderableWrapper(RenderableBase* real) {
        if (dynamic_cast<RenderableUI*>(real))
            throw std::invalid_argument("Cannot handle UI!");

        _real = real;
    }

    void render() override {
        _real->render();
    }
};

class RenderableWrapperUI : public RenderableUI, public Updatable {
private:
    RenderableUI* _real;
public:
    RenderableWrapperUI(RenderableUI* real) : RenderableUI(real->getTexture()) {
        _real = real;
    }

    void render() override {
        _real->render();
    }
};