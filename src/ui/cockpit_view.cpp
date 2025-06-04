#include "ui/cockpit_view.hpp"

#include "ui/star_map_view.hpp"
#include "ui/terminal_view.hpp"

#include <raylib.h>

#include "core/loaders.hpp"

CockpitView::CockpitView(StarMapView* starMapView, TerminalView* terminalView) {
    _starMapTexture = Loaders::Texture.get("assets/textures/star_map_cockpit.png");
    _terminalTexture = Loaders::Texture.get("assets/textures/terminal_cockpit.png");

    _starMapView = starMapView;
    _terminalView = terminalView;

    hideView(_starMapView);
    hideView(_terminalView);
}

void CockpitView::hideView(RenderableUI* view) {
    if (view == nullptr)
        return;
    view->setShouldUpdate(false);
    view->setHidden(true);
}

void CockpitView::switchView(RenderableUI* view) {
    hideView(_currentView);
    _currentView = view;
    if (_currentView == nullptr)
        return;
    _currentView->setHidden(false);
    _currentView->setShouldUpdate(true);
}
bool CockpitView::handleMouse(Vector2 coords, bool left, bool right) {
    if (left) {
        if (CheckCollisionPointRec(coords, _terminalInfo)) {
            switchView(_terminalView);
            return true;
        }
        if (CheckCollisionPointRec(coords, _starMapInfo)) {
            switchView(_starMapView);
            return true;
        }
    }

    return false;
};

void CockpitView::render() {
    renderOne(_terminalTexture, { 0, 0, _terminalInfo.width, _terminalInfo.height }, _terminalInfo);
    renderOne(_starMapTexture, { 0, 0, _starMapInfo.width, _starMapInfo.height }, _starMapInfo);
}

void CockpitView::update() {
    if (IsKeyDown(KEY_ESCAPE))
        switchView(nullptr);
}