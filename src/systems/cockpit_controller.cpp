#include "cockpit_controller.hpp"

#include "ui/star_map_view.hpp"
#include "ui/terminal_view.hpp"

#include <raylib.h>

CockpitController::CockpitController(StarMapView* starMapView, TerminalView* terminalView) {
    _starMapView = starMapView;
    _terminalView = terminalView;
    _starMapView->setHidden(true);
    _terminalView->setHidden(true);
}

void CockpitController::update() {
    if (_currentView == nullptr) {
        if (IsKeyPressed(KEY_T)) {
            _currentView = _terminalView;
            _currentView->setHidden(false);
        }
        if (IsKeyPressed(KEY_S)) {
            _currentView = _starMapView;
            _currentView->setHidden(false);
        }
    }
    else {
        if (_currentView == _terminalView) {
            _terminalView->takeInput();
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            _currentView->setHidden(true);
            _currentView = nullptr;
        }
    }
}