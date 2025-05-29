#include "core/renderer.hpp"
#include "core/render_stack.hpp"
#include "core/renderable_base.hpp"
#include "core/renderable_UI.hpp"

Camera* Renderer::_camera = nullptr;

int Renderer::_width; 
int  Renderer::_height;
RenderTexture  Renderer::_renderTexture;

void Renderer::init(int width, int height) {
    _width = width;
    _height = height;
    _renderTexture = LoadRenderTexture(width, height);
}

void Renderer::render(RenderStack& stack) {
        BeginTextureMode(_renderTexture);

        ClearBackground(BLACK);

        
        BeginMode3D(*Renderer::getCamera());
        
        for (auto renderable : stack.getPerspective())
            renderable->render();

        EndMode3D();

        for (auto uiElement : stack.getOrthographic())
            uiElement->render();

        EndTextureMode();

        BeginDrawing();

        DrawTexturePro(_renderTexture.texture, {0, 0, 1.0f * _width, -1.0f * _height}, {0, 0, 2.0f * _width, 2.0f * _height}, {0, 0}, 0.0f, WHITE);

        EndDrawing();
}