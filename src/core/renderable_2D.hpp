#pragma once

#include <raylib.h>
#include "core/renderable_base.hpp"
#include "core/renderer.hpp"

class Renderable2D : public RenderableBase {
private:
    Vector2 position;
    float scale;
    float rotation;
    Texture* _texture;
    Rectangle _textureRect;
public:
    Renderable2D(Texture* texture) {
        _texture = texture;
        _textureRect = { 0.0f, 0.0f, 1.0f * _texture->width, 1.0f * _texture->height };
    }

    void render() override {
        // Get camera information
        DrawBillboardRec(*Renderer::getCamera(), *_texture, _textureRect, _position, { _scale, _scale }, WHITE);
    }
};