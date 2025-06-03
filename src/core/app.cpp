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
#include "systems/cockpit_controller.hpp"
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

    auto terminal = new Terminal();
    scene->spawn(terminal);

    auto view = new TerminalView(terminal, 640, 480);
    scene->spawn(view);

    auto starMapView = new StarMapView(480);
    scene->spawn(starMapView);

    auto cockpitController = new CockpitController(starMapView, view);
    scene->spawn(cockpitController);

    while(!WindowShouldClose()) {
        if (IsWindowResized())
            Renderer::calculateRatio(GetScreenWidth(), GetScreenHeight());

        SceneHandler::getCurrent()->updateAll();

        Vector2 mousePos = Vector2Scale(Vector2Subtract(GetMousePosition(), Renderer::getCanvasPosition()), 1.0f / Renderer::getRatio());

        auto ui = SceneHandler::getCurrent()->getRenderStack()->getOrthographic();
        for (auto it = ui.rbegin(); it != ui.rend(); it++)
            if ((*it)->handleMouse(mousePos, false, false))
                break; // handled


        // view->takeInput();

        Renderer::render(*SceneHandler::getCurrent()->getRenderStack());
    }
}