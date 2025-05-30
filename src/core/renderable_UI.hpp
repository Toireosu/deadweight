#pragma once

#include "core/renderable_base.hpp"
#include <raymath.h>

class RenderableUI : public RenderableBase {
protected:
    Texture* _texture;
    Rectangle _textureRect;
public:
    RenderableUI(Texture* texture) {
        _texture = texture;
        _textureRect = {0, 0, 1.0f * _texture->width, 1.0f * _texture->height };
    }

    RenderableUI() {
        _texture = nullptr;
    }

    virtual void render() {
        DrawTexturePro(*_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale }, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    Texture* getTexture() { return _texture; }
};