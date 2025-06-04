#pragma once

#include "core/renderable_base.hpp"
#include <raymath.h>

class RenderableUI : public RenderableBase {
protected:
    Texture* _texture;
    Rectangle _textureRect;
protected:
    void renderOne(Texture* texture, Rectangle srcRect, Rectangle dstRect) {
        DrawTexturePro(*texture, srcRect, dstRect, {0.0f, 0.0f}, 0.0f, WHITE);
    }
public:
    RenderableUI(Texture* texture) {
        _texture = texture;
        _textureRect = {0, 0, 1.0f * _texture->width, 1.0f * _texture->height };
    }

    RenderableUI() {
        _texture = nullptr;
    }

    // Returns true if handled else false
    virtual bool handleMouse(Vector2 coords, bool left, bool right) {
        return false;
    }

    bool runHandleMouse(Vector2 coords, bool left, bool right) {
        if (_shouldUpdate || !_hidden)
            return handleMouse(coords, left, right);
        return false;
    }

    virtual void render() override {
        // DrawTexturePro(*_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale }, {0.0f, 0.0f}, 0.0f, WHITE);
        renderOne(_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale });
    }

    Texture* getTexture() { return _texture; }
};