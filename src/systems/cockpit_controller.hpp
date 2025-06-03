#pragma once

#include "core/updatable.hpp"
#include "core/renderable_UI.hpp"

class StarMapView;
class TerminalView;
class CockpitController : public Updatable {
private:
    RenderableUI* _currentView = nullptr;
    StarMapView* _starMapView;
    TerminalView* _terminalView;
public:
    CockpitController(StarMapView* starMapView, TerminalView* terminalView);

    void update() override;
};