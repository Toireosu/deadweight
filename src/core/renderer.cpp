#include "core/renderer.hpp"
#include "core/render_stack.hpp"
#include "core/renderable_base.hpp"
#include "core/renderable_UI.hpp"
#include <rlgl.h>

#include <rlgl.h>

Camera* Renderer::_camera = nullptr;

int Renderer::_width; 
int  Renderer::_height;
RenderTexture  Renderer::_renderTexture;
float Renderer::_ratio = 1.0f;
Vector2 Renderer::_pos;

void Renderer::init(int width, int height) {
    _width = width;
    _height = height;
    _renderTexture = LoadRenderTexture(width, height);
    rlSetClipPlanes(0.1, 10000.0f);
}

void Renderer::calculateRatio(int width, int height) {
    _ratio = 1.0f * width / _width;
    if (_height * _ratio > height) {
        _ratio = 1.0f * height / _height;
    }

    _pos.x = (width - _width * _ratio) / 2.0f;
    _pos.y = (height - _height * _ratio) / 2.0f;
}

void Renderer::render(RenderStack& stack) {
        BeginTextureMode(_renderTexture);

        ClearBackground(BLACK);
        BeginMode3D(*Renderer::getCamera());
        
        for (auto renderable : stack.getPerspective())
            renderable->renderCall();

        EndMode3D();

        // Hack to allow 3D models in UI
        rlSetMatrixModelview(MatrixOrtho(-1, 1, -1, 1, 0.1, 100));

        for (auto uiElement : stack.getOrthographic())
            uiElement->renderCall();

        EndTextureMode();

        BeginDrawing();

        DrawTexturePro(_renderTexture.texture, {0, 0, 1.0f * _width, -1.0f * _height}, {_pos.x, _pos.y, _ratio * _width, _ratio * _height}, {0, 0}, 0.0f, WHITE);

        EndDrawing();
}