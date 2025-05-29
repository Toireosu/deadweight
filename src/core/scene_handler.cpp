#include "core/scene_handler.hpp"
#include "core/scene.hpp"

Scene* SceneHandler::_current = nullptr;
void SceneHandler::switchScene(Scene* scene) {
    delete _current;
    _current = scene;
    _current->init();
}
