#pragma once

#include "core/renderable_UI.hpp"
#include "core/updatable.hpp"

#include "systems/terminal.hpp"
#include <sstream>

#include <raymath.h>
#include <rlgl.h>
#include <cctype>

class Terminal;
class TerminalView : public RenderableUI, public Updatable {
private:
    RenderTexture _preRenderTexture;
    Font _font;
    Terminal* _terminal;
    int _lineIndex = 0;
    float _lineHeight = 18;
    Vector2 _screenBounds = { 32, 32 };

    std::stringstream _inputStream;

    Color _terminalColor = GREEN;
    Color _terminalError = RED;

    void clear() {
        _lineIndex = 0;
    }

    void writeLine(std::string line, bool error) {
        DrawTextEx(_font, line.c_str(), Vector2Add(_screenBounds, {0, _lineHeight * _lineIndex }), 15, 4, error ? _terminalError : _terminalColor);
        _lineIndex++;
    }

public:
    TerminalView(Terminal* terminal, int width, int height) : RenderableUI() {
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
    
        _font = LoadFontEx("assets\\fonts\\consola.ttf", 100, nullptr, 0);
        _terminal = terminal; 
    }

    ~TerminalView() {
        UnloadRenderTexture(_preRenderTexture);
    }

    void takeInput() {
        int key = GetKeyPressed();

        std::string str = _inputStream.str();
        switch (key) {
            case KEY_ENTER:
                if (str.empty())
                    return;
                _terminal->handleInput(str);
                _inputStream.str("");
                _inputStream.clear();
            return;
            case KEY_BACKSPACE:
                if (!str.empty()) {
                    _inputStream.str("");
                    _inputStream.clear();
                    _inputStream << str.erase(str.size() - 1);
                }
            return;
            case KEY_SPACE:
                _inputStream << ' ';
            return;
        }

        char c = GetCharPressed();
        if (!std::isalpha(c))
            return;

        _inputStream << c;
    }

    void render() override {
        RenderableUI::render();

        clear();

        writeLine(_terminal->getGreetingMessage(), false);
        if (!_terminal->getOutput().empty())
            writeLine(_terminal->getOutput(), _terminal->getWasError());
        writeLine((_inputStream.str() + "_"), false);
    }
};