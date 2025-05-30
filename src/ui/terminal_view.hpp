#pragma once

#include "core/renderable_UI.hpp"
#include "core/updatable.hpp"

#include "rlgl.h"

class TerminalView : public RenderableUI, public Updatable {
private:
    RenderTexture _preRenderTexture;
    Font font;
public:
    TerminalView(int width, int height) : RenderableUI() {
        Texture tileTexture = LoadTexture("assets/textures/terminal.png");
        _preRenderTexture = LoadRenderTexture(width, height);
        
        BeginTextureMode(_preRenderTexture);

        int iWidth = width / 16;
        int iHeight = height / 16;
        for (int y = 0; y < iHeight; y++) {
            for (int x = 0; x < iWidth; x++) {
                Rectangle rect = {16, 16, 16, 16};

                rect.x = ((x == iWidth - 1) ? 32 : ((x == 0) ? 0 : 16));
                rect.y = ((y == iHeight - 1) ? 32 : ((y == 0) ? 0 : 16));

                DrawTextureRec(tileTexture, rect, {16.0f * x, 16.0f * y}, WHITE);
            }
        }
        EndTextureMode();
        UnloadTexture(tileTexture);
        
        _texture = &_preRenderTexture.texture;
        _textureRect = { 0, 0, 1.0f * width, -1.0f * height };
    
        // font = GetFontDefault();
        font = LoadFont("smalle.fon");
    }

    ~TerminalView() {
        UnloadRenderTexture(_preRenderTexture);
    }

    void render() override {
        RenderableUI::render();

        DrawTextEx(font, "Test...", { 16, 16 }, 10, 4, GREEN);
    }
};