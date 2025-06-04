#pragma once

#include "core/renderable_UI.hpp"

#include <raylib.h>

class StarMapView;
class TerminalView; 
class CockpitView : public RenderableUI {
private: 
    RenderableUI* _currentView = nullptr;
    StarMapView* _starMapView;
    TerminalView* _terminalView;

    Texture* _terminalTexture;
    Texture* _starMapTexture;

    Rectangle _terminalInfo = { 200, 200, 120, 120 };
    Rectangle _starMapInfo = { 600, 400, 128, 64 };

public: 
    CockpitView(StarMapView* starMapView, TerminalView* terminalView);
    void hideView(RenderableUI* view);
    void switchView(RenderableUI* view);
    bool handleMouse(Vector2 coords, bool left, bool right) override;
    void render() override;
    void update() override;
};