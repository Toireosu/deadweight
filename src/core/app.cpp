#include "core/app.hpp"
#include "core/renderable_2D.hpp"
#include "core/renderable_3D.hpp"
#include "core/renderable_UI.hpp"
#include "core/render_stack.hpp"
#include "core/scene.hpp"
#include "core/scene_handler.hpp"
#include "ui/terminal_view.hpp"
#include "core/loaders.hpp"
#include "data/world_map.hpp"
#include "ui/star_map_view.hpp"
#include "ui/cockpit_view.hpp"
#include "systems/world_renderer.hpp"
#include <sstream>
#include <iostream>

App::App() {
    // Respect settings
    InitWindow(1600, 900, "Deadweight");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetExitKey(KEY_NULL);

    // Init renderer 
    Renderer::init(854, 480);
    Renderer::calculateRatio(GetScreenWidth(), GetScreenHeight());

    // Init audio device
    InitAudioDevice();

    // Init world map
    WorldMap::init();
}

void App::run() {
    Model model = LoadModelFromMesh(GenMeshSphere(1.0f, 8, 8));
    Renderable3D r3d(&model);
    
    Camera c3d = { { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    Renderer::setCamera(&c3d);

    Scene* scene = new Scene();
    SceneHandler::switchScene(scene);

    auto playerVessel = new PlayerVessel(SpaceCoords(230, 450));

    auto worldRenderer = new WorldRenderer();
    playerVessel->addListener(worldRenderer);
    scene->spawn(worldRenderer);

    playerVessel->hasMovedCoords();

    auto terminal = new Terminal(playerVessel);
    scene->spawn(terminal);

    auto view = new TerminalView(terminal, 640, 480);
    auto starMapView = new StarMapView(480, playerVessel);
    
    auto cockpitView = new CockpitView(starMapView, view);
    scene->spawn(cockpitView);
    
    scene->spawn(view);

    scene->spawn(starMapView);
    while(!WindowShouldClose()) {
        if (IsWindowResized())
            Renderer::calculateRatio(GetScreenWidth(), GetScreenHeight());

        SceneHandler::getCurrent()->updateAll();

        Vector2 mousePos = Vector2Scale(Vector2Subtract(GetMousePosition(), Renderer::getCanvasPosition()), 1.0f / Renderer::getRatio());

        auto ui = SceneHandler::getCurrent()->getRenderStack()->getOrthographic();
        for (auto it = ui.rbegin(); it != ui.rend(); it++)
            if ((*it)->runHandleMouse(mousePos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON), IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)))
                break; // handled


        // view->takeInput();

        Renderer::render(*SceneHandler::getCurrent()->getRenderStack());
    }
}