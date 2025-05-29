#include "core/app.hpp"
#include "core/renderable_2D.hpp"
#include "core/renderable_3D.hpp"
#include "core/renderable_UI.hpp"
#include "core/render_stack.hpp"

App::App() {
    // Respect settings
    InitWindow(1200, 900, "Deadweight");
    // Init renderer if needed
    Renderer::init(640, 400);
}

void App::run() {
    Texture texture = LoadTexture("assets/textures/gullbert.png");
    Renderable2D r2d(&texture);
    r2d.setPosition({ -5.0f, 0.0f, 0.0f });
    Model model = LoadModelFromMesh(GenMeshSphere(1.0f, 8, 8));
    Renderable3D r3d(&model);
    
    Camera c3d = { { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    Renderer::setCamera(&c3d);
    
    RenderStack stack;
    stack.add(&r2d);
    stack.add(&r3d);
    stack.add(new RenderableUI(&texture));
   
    while(!WindowShouldClose()) {
        Renderer::render(stack);
    }
}