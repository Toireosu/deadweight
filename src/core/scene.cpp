#include "core/scene.hpp"

#include "core/updatable.hpp"
#include "core/renderable_base.hpp"

void Scene::init() { }

void Scene::destroyAll() {
    for (auto updatable : std::list(_updatables))
        destroy(updatable);
}  

Scene::~Scene() {
    destroyAll();
}

void Scene::spawn(Updatable* updatable) {
    auto renderable = dynamic_cast<RenderableBase*>(updatable);

    if (renderable)
        _renderStack.add(renderable);

    _updatables.push_back(updatable);
}

void Scene::destroy(Updatable* updatable) {
    auto renderable = dynamic_cast<RenderableBase*>(updatable);

    if (renderable)
        _renderStack.remove(renderable);

    _updatables.remove(updatable);
    delete updatable;
}

void Scene::updateAll() {
    for (auto updatable : std::list(_updatables))
        updatable->update();
}