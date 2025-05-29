#pragma once

class Scene;
class SceneHandler {
private:
    static Scene* _current;
public:
    static void switchScene(Scene* scene);
    static Scene* getCurrent() { return _current; }
};