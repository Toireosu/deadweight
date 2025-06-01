#pragma once

#include "core/renderable_UI.hpp"

#include "systems/terminal.hpp"
#include <sstream>

#include <raymath.h>
#include <rlgl.h>
#include <cctype>
#include <cmath>

#include "core/loaders.hpp"

class Terminal;
class TerminalView : public RenderableUI {
private:
    // Rendering
    RenderTexture _preRenderTexture;
    Font* _font;
    Terminal* _terminal;
    int _lineIndex = 0;
    float _lineHeight = 18;
    Vector2 _screenBounds = { 32, 32 };
    Color _terminalColor = GREEN;
    Color _terminalError = RED;

    void clearTerminal() {
        _lineIndex = 0;
    }

    void writeLine(std::string line, bool error) {
        DrawTextEx(*_font, line.c_str(), Vector2Add(_screenBounds, {0, _lineHeight * _lineIndex }), 15, 4, error ? _terminalError : _terminalColor);
        _lineIndex++;
    }

    // Sounds
    Sound* _inputSound;
    Sound* _acceptSound;
    
    // Input

    int _historyIndex = -1;
    std::stringstream _inputStream;

    bool isValidCharIn(char c) {
        return  
            std::isdigit(c) ||
            std::isalpha(c) ||
            c == '_' ||
            c == '-' ||
            c == '.' ||
            c == ',' ||
            c == ' ';
    }

    void resetHistory() {
        _historyIndex = -1;
    }

    void clearInput() {
        _inputStream.str("");
        _inputStream.clear();
    }

    template <typename T>
    void appendInput(T addition, bool clear) {
        if (clear)
            clearInput();
        _inputStream << addition;
        PlaySound(*_inputSound);
    }

public:
    TerminalView(Terminal* terminal, int width, int height) : RenderableUI() {
        Texture& tileTexture = *Loaders::Texture.get("assets/textures/terminal.png");
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
        
        _texture = &_preRenderTexture.texture;
        _textureRect = { 0, 0, 1.0f * width, -1.0f * height };
    
        _font = Loaders::Font.get("assets/fonts/consola.ttf");
        _inputSound = Loaders::Sound.get("assets/audio/sounds/dig_click.wav");
        _acceptSound = Loaders::Sound.get("assets/audio/sounds/dig_accept.wav");
        _terminal = terminal; 
    }

    ~TerminalView() {
        UnloadRenderTexture(_preRenderTexture);
    }

    void takeInput() {

        std::string str = _inputStream.str();
        if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
            if (!str.empty()) {
                appendInput(str.erase(str.size() - 1), true);
                resetHistory();
            }

            return;
        }

        if (IsKeyPressed(KEY_ENTER)) {
                if (!str.empty()) {
                    _terminal->handleInput(str);
                    clearInput();
                    resetHistory();
                    PlaySound(*_acceptSound);
                }
            return;
        }

        if (IsKeyPressed(KEY_UP)) {
            appendInput(_terminal->getInput(++_historyIndex), true);
            return;
        }

        if (IsKeyPressed(KEY_DOWN)) {
            _historyIndex = fmax(--_historyIndex, -1);
            appendInput(_terminal->getInput(_historyIndex), true);
            return;
        }

        char c = GetCharPressed();
        if (!isValidCharIn(c))
            return;

        appendInput(c, false);
    }

    void render() override {
        RenderableUI::render();

        clearTerminal();

        writeLine(_terminal->getGreetingMessage(), false);
        if (!_terminal->getOutput().empty()) {
            for (auto line : _terminal->getOutput())
            writeLine(line, _terminal->getWasError());
        }

        if (int(GetTime() * 2) % 2)
            writeLine((_inputStream.str() + "_"), false);
        else
            writeLine((_inputStream.str()), false);
    }
};