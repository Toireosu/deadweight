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

App::App() {
    // Respect settings
    InitWindow(1600, 900, "Deadweight");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Init renderer 
    Renderer::init(640, 360);
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

    // auto terminal = new Terminal();
    // scene->spawn(terminal);

    // auto view = new TerminalView(terminal, 640, 360);
    // scene->spawn(view);

    auto starMapView = new StarMapView(360);
    scene->spawn(starMapView);

    while(!WindowShouldClose()) {
        if (IsWindowResized())
            Renderer::calculateRatio(GetScreenWidth(), GetScreenHeight());

        SceneHandler::getCurrent()->updateAll();

        // view->takeInput();

        Renderer::render(*SceneHandler::getCurrent()->getRenderStack());
    }
}